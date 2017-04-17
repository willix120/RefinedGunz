#pragma once

#include <string>
#include <memory>
#include <algorithm>
#include "TMP.h"
#include "GlobalTypes.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifdef SAFE_RELEASE
#undef SAFE_RELEASE
#endif

template <typename T>
inline void SafeRelease(T& ptr)
{
	if (!ptr)
		return;
	ptr->Release();
	ptr = nullptr;
}

struct D3DDeleter {
	void operator()(struct IUnknown* ptr) const;
};

template <typename T>
using D3DPtr = std::unique_ptr<T, D3DDeleter>;

template <typename T>
inline void SafeRelease(D3DPtr<T>& ptr)
{
	ptr = nullptr;
}

using WIN_DWORD_PTR = std::conditional_t<sizeof(void*) == 4, unsigned long, unsigned long long>;

#define SAFE_RELEASE(p)      { SafeRelease(p); }

#define EXPAND_VECTOR(v) v[0], v[1], v[2]

#define SetBitSet(sets, item)		(sets |= (1 << item))
#define ClearBitSet(sets, item)		(sets &= ~(1 << item))
#define CheckBitSet(sets, item)		(sets & (1 << item))

#ifdef _MSC_VER
#define WARN_UNUSED_RESULT _Check_return_
#define STDCALL __stdcall
#else
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#define STDCALL __attribute__((stdcall))
#endif

#define TOKENIZE_IMPL(a, b) a##b
#define TOKENIZE(a, b) TOKENIZE_IMPL(a, b)

inline constexpr uint32_t ARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

inline constexpr uint32_t RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ARGB(a, r, g, b);
}

inline constexpr uint32_t XRGB(uint8_t r, uint8_t g, uint8_t b)
{
	return ARGB(0xFF, r, g, b);
}

inline constexpr uint32_t XRGB(uint8_t value)
{
	return XRGB(value, value, value);
}

enum MDateType
{
	MDT_Y = 1,
	MDT_YM,
	MDT_YMD,
	MDT_YMDH,
	MDT_YMDHM,
};

std::string MGetStrLocalTime(unsigned short wYear = 0,
	unsigned short wMon = 0,
	unsigned short wDay = 0,
	unsigned short wHour = 0,
	unsigned short wMin = 0,
	MDateType = MDT_YMDHM);

template <typename T1, typename T2>
T1 reinterpret(const T2& val)
{
	static_assert(std::is_trivially_copyable<T1>::value &&
		std::is_trivially_copyable<T2>::value,
		"Both types must be trivially copyable to reinterpret");
	static_assert(!std::is_pointer<T2>::value, "Use reinterpret_ptr for pointers");
	T1 T1_rep;
	memcpy(&T1_rep, &val, (std::min)(sizeof(T1), sizeof(T2)));
	return T1_rep;
}

template <typename T1, typename T2>
T1 reinterpret_ptr(const T2& val)
{
	static_assert(std::is_trivially_copyable<T1>::value &&
		std::is_trivially_copyable<T2>::value,
		"Both types must be trivially copyable to reinterpret");
	T1 T1_rep;
	memcpy(&T1_rep, &val, (std::min)(sizeof(T1), sizeof(T2)));
	return T1_rep;
}

template <typename T>
struct Range
{
	T first;
	T second;

	auto begin() { return first; }
	auto end() { return second; }
	auto begin() const { return first; }
	auto end() const { return second; }
};

template <typename T>
auto MakeRange(const T& begin, const T& end) { return Range<T>{ begin, end }; }

template <template <typename...> class itT, typename T>
auto MakeAdapter(T& Container) {
	return MakeRange(
		itT<decltype(Container.begin())>{ Container.begin() },
		itT<decltype(Container.end())>{ Container.end() });
}

template <typename ItT>
class ValueIterator
{
public:
	ValueIterator(ItT i) : it(i) { }

	ValueIterator& operator++()
	{
		++it;
		return *this;
	}

	ValueIterator operator++(int)
	{
		auto temp(*this);
		++*this;
		return temp;
	}

	bool operator==(const ValueIterator& rhs) const { return it == rhs.it; }
	bool operator!=(const ValueIterator& rhs) const { return it != rhs.it; }
	auto& operator*() { return it->second; }
	auto& operator->() { return this->operator*(); }

private:
	ItT it;
};

// Returns an adapter whose iterators returns .second of the pair that
// iterators of the original container return, i.e. the values of a map.
template <typename T>
auto MakePairValueAdapter(T& Container) { return MakeAdapter<ValueIterator>(Container); }

inline std::pair<bool, int> StringToInt(const char* String, int Radix = 10)
{
	char *endptr = nullptr;

	int IntVal = strtol(String, &endptr, Radix);

	if (endptr != String + strlen(String))
		return{ false, -1 };

	return{ true, IntVal };
}

// WriteProxy
// A class that acts as a pointer-to-pointer wrapper for smart pointers for passing to functions
// that expect to "return" a pointer by writing to a pointer-to-pointer argument.
// Should only ever be instantiated by MakeWriteProxy as a temporary for a argument.
// The smart pointer will then have the returned value (if set) after the full expression it appears in.
//
// Example:
// void foo(int**); std::unique_ptr<int> ptr; foo(MakeWriteProxy(ptr));
template <typename T>
class WriteProxy
{
	using StoredType = get_template_argument_t<T, 0>;
public:
	~WriteProxy() { ptr = T{ temp }; }

	operator StoredType**() && { return &temp; }

private:
	WriteProxy(T& ptr) : ptr(ptr), temp(ptr.get()) {}
	WriteProxy(const WriteProxy&) = delete;
	WriteProxy& operator=(const WriteProxy&) = delete;

	template <typename... U>
	friend WriteProxy<std::unique_ptr<U...>> MakeWriteProxy(std::unique_ptr<U...>&);

	T& ptr;
	StoredType* temp{};
};

template <typename... T>
WriteProxy<std::unique_ptr<T...>> MakeWriteProxy(std::unique_ptr<T...>& ptr) {
	return{ ptr };
}

// Converts an rvalue to a mutable lvalue
template <typename T>
T& unmove(T&& x) { return x; }

// Returns value rounded up towards the nearest power of two
inline u32 NextPowerOfTwo(u32 value)
{
	unsigned long rightmost_bit;
	if (!_BitScanReverse(&rightmost_bit, value))
		return 2;
	auto rightmost_bit_value = 1 << rightmost_bit;
	if ((value ^ rightmost_bit_value) != 0)
		rightmost_bit_value <<= 1;
	return rightmost_bit_value;
}

template <typename ContainerType, typename ValueType>
void erase_remove(ContainerType&& Container, ValueType&& Value) {
	Container.erase(std::remove(Container.begin(), Container.end(), Value), Container.end());
}

template <typename ContainerType, typename PredicateType>
void erase_remove_if(ContainerType&& Container, PredicateType&& Predicate) {
	Container.erase(std::remove_if(Container.begin(), Container.end(),
		std::forward<PredicateType>(Predicate)),
		Container.end());
}

struct CFileCloser {
	void operator()(FILE* ptr) const {
		if (ptr)
			fclose(ptr);
	}
};

using CFilePtr = std::unique_ptr<FILE, CFileCloser>;