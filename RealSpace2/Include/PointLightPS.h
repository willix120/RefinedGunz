#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//   fxc /Eps_point_light /Tps_3_0 /FhInclude/PointLightPS.h
//    /VnPointLightPSData Source/Lighting.hlsl /O3
//
//
// Parameters:
//
//   sampler2D depthTexture;
//   sampler2D diffuseTexture;
//   float g_Far;
//   float2 g_InvFocalLen;
//   float2 g_InvRes;
//   float4 g_Light;
//   float3 g_LightColor;
//   float g_Near;
//   sampler2D normalTexture;
//
//
// Registers:
//
//   Name           Reg   Size
//   -------------- ----- ----
//   g_InvRes       c4       1
//   g_Near         c5       1
//   g_Far          c6       1
//   g_Light        c8       1
//   g_LightColor   c9       1
//   g_InvFocalLen  c10      1
//   diffuseTexture s0       1
//   normalTexture  s1       1
//   depthTexture   s2       1
//

    ps_3_0
    def c0, 0.5, 1, 0, -2
    def c1, 32, 0, 0, 0
    dcl_texcoord v0.xyw
    dcl_2d s0
    dcl_2d s1
    dcl_2d s2
    rcp r0.x, v0.w
    mul r0.xy, r0.x, v0
    mul r0.zw, r0.xyxy, c10.xyxy
    mad r1.xy, r0, c0.x, c0.x
    mov r1.z, -r1.y
    mov r0.x, c0.x
    mad r0.xy, c4, r0.x, r1.xzzw
    texld r1, r0, s2
    mov r2.x, c5.x
    add r1.y, -r2.x, c6.x
    mad r1.z, r1.x, r1.y, c5.x
    mul r1.xy, r0.zwzw, r1.z
    dp3 r0.z, -r1, -r1
    rsq r0.z, r0.z
    add r2.xyz, -r1, c8
    dp3 r0.w, r2, r2
    rsq r0.w, r0.w
    mul r2.xyz, r0.w, r2
    rcp r0.w, r0.w
    mad r1.xyz, -r1, r0.z, r2
    nrm r3.xyz, r1
    texld r1, r0, s1
    texld r4, r0, s0
    mad r0.xyz, r1, -c0.w, -c0.y
    dp3_sat r1.x, r3, r0
    dp3_sat r0.x, r0, r2
    mul r0.y, r4.w, c1.x
    pow r2.x, r1.x, r0.y
    mad r0.xyz, r4, r0.x, r2.x
    mul r0.xyz, r0, c9
    rcp r1.x, c8.w
    mul r0.w, r0.w, r1.x
    mad r0.w, r0.w, -r0.w, c0.y
    max r1.x, r0.w, c0.z
    mul oC0.xyz, r0, r1.x
    mov oC0.w, c0.y

// approximately 40 instruction slots used (3 texture, 37 arithmetic)
#endif

const BYTE PointLightPSData[] =
{
      0,   3, 255, 255, 254, 255, 
    124,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 187,   1, 
      0,   0,   0,   3, 255, 255, 
      9,   0,   0,   0,  28,   0, 
      0,   0,   0, 129,   0,   0, 
    180,   1,   0,   0, 208,   0, 
      0,   0,   3,   0,   2,   0, 
      1,   0,  10,   0, 224,   0, 
      0,   0,   0,   0,   0,   0, 
    240,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   2,   0, 
      0,   1,   0,   0,   0,   0, 
      0,   0,  16,   1,   0,   0, 
      2,   0,   6,   0,   1,   0, 
     26,   0,  24,   1,   0,   0, 
      0,   0,   0,   0,  40,   1, 
      0,   0,   2,   0,  10,   0, 
      1,   0,  42,   0,  56,   1, 
      0,   0,   0,   0,   0,   0, 
     72,   1,   0,   0,   2,   0, 
      4,   0,   1,   0,  18,   0, 
     56,   1,   0,   0,   0,   0, 
      0,   0,  81,   1,   0,   0, 
      2,   0,   8,   0,   1,   0, 
     34,   0,  92,   1,   0,   0, 
      0,   0,   0,   0, 108,   1, 
      0,   0,   2,   0,   9,   0, 
      1,   0,  38,   0, 124,   1, 
      0,   0,   0,   0,   0,   0, 
    140,   1,   0,   0,   2,   0, 
      5,   0,   1,   0,  22,   0, 
     24,   1,   0,   0,   0,   0, 
      0,   0, 147,   1,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      6,   0, 164,   1,   0,   0, 
      0,   0,   0,   0, 100, 101, 
    112, 116, 104,  84, 101, 120, 
    116, 117, 114, 101,   0, 171, 
    171, 171,   4,   0,  12,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    100, 105, 102, 102, 117, 115, 
    101,  84, 101, 120, 116, 117, 
    114, 101,   0, 171,   4,   0, 
     12,   0,   1,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 103,  95,  70,  97, 
    114,   0, 171, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0, 103,  95,  73, 110, 
    118,  70, 111,  99,  97, 108, 
     76, 101, 110,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 103,  95, 
     73, 110, 118,  82, 101, 115, 
      0, 103,  95,  76, 105, 103, 
    104, 116,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 103,  95, 
     76, 105, 103, 104, 116,  67, 
    111, 108, 111, 114,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   3,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    103,  95,  78, 101,  97, 114, 
      0, 110, 111, 114, 109,  97, 
    108,  84, 101, 120, 116, 117, 
    114, 101,   0, 171, 171, 171, 
      4,   0,  12,   0,   1,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 112, 115, 
     95,  51,  95,  48,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  57,  46, 
     50,  57,  46,  57,  53,  50, 
     46,  51,  49,  49,  49,   0, 
     81,   0,   0,   5,   0,   0, 
     15, 160,   0,   0,   0,  63, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0, 192, 
     81,   0,   0,   5,   1,   0, 
     15, 160,   0,   0,   0,  66, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  11, 144, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   1,   8,  15, 160, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   2,   8,  15, 160, 
      6,   0,   0,   2,   0,   0, 
      1, 128,   0,   0, 255, 144, 
      5,   0,   0,   3,   0,   0, 
      3, 128,   0,   0,   0, 128, 
      0,   0, 228, 144,   5,   0, 
      0,   3,   0,   0,  12, 128, 
      0,   0,  68, 128,  10,   0, 
     68, 160,   4,   0,   0,   4, 
      1,   0,   3, 128,   0,   0, 
    228, 128,   0,   0,   0, 160, 
      0,   0,   0, 160,   1,   0, 
      0,   2,   1,   0,   4, 128, 
      1,   0,  85, 129,   1,   0, 
      0,   2,   0,   0,   1, 128, 
      0,   0,   0, 160,   4,   0, 
      0,   4,   0,   0,   3, 128, 
      4,   0, 228, 160,   0,   0, 
      0, 128,   1,   0, 232, 128, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   0,   0, 228, 128, 
      2,   8, 228, 160,   1,   0, 
      0,   2,   2,   0,   1, 128, 
      5,   0,   0, 160,   2,   0, 
      0,   3,   1,   0,   2, 128, 
      2,   0,   0, 129,   6,   0, 
      0, 160,   4,   0,   0,   4, 
      1,   0,   4, 128,   1,   0, 
      0, 128,   1,   0,  85, 128, 
      5,   0,   0, 160,   5,   0, 
      0,   3,   1,   0,   3, 128, 
      0,   0, 238, 128,   1,   0, 
    170, 128,   8,   0,   0,   3, 
      0,   0,   4, 128,   1,   0, 
    228, 129,   1,   0, 228, 129, 
      7,   0,   0,   2,   0,   0, 
      4, 128,   0,   0, 170, 128, 
      2,   0,   0,   3,   2,   0, 
      7, 128,   1,   0, 228, 129, 
      8,   0, 228, 160,   8,   0, 
      0,   3,   0,   0,   8, 128, 
      2,   0, 228, 128,   2,   0, 
    228, 128,   7,   0,   0,   2, 
      0,   0,   8, 128,   0,   0, 
    255, 128,   5,   0,   0,   3, 
      2,   0,   7, 128,   0,   0, 
    255, 128,   2,   0, 228, 128, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   0,   0, 255, 128, 
      4,   0,   0,   4,   1,   0, 
      7, 128,   1,   0, 228, 129, 
      0,   0, 170, 128,   2,   0, 
    228, 128,  36,   0,   0,   2, 
      3,   0,   7, 128,   1,   0, 
    228, 128,  66,   0,   0,   3, 
      1,   0,  15, 128,   0,   0, 
    228, 128,   1,   8, 228, 160, 
     66,   0,   0,   3,   4,   0, 
     15, 128,   0,   0, 228, 128, 
      0,   8, 228, 160,   4,   0, 
      0,   4,   0,   0,   7, 128, 
      1,   0, 228, 128,   0,   0, 
    255, 161,   0,   0,  85, 161, 
      8,   0,   0,   3,   1,   0, 
     17, 128,   3,   0, 228, 128, 
      0,   0, 228, 128,   8,   0, 
      0,   3,   0,   0,  17, 128, 
      0,   0, 228, 128,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,   2, 128,   4,   0, 
    255, 128,   1,   0,   0, 160, 
     32,   0,   0,   3,   2,   0, 
      1, 128,   1,   0,   0, 128, 
      0,   0,  85, 128,   4,   0, 
      0,   4,   0,   0,   7, 128, 
      4,   0, 228, 128,   0,   0, 
      0, 128,   2,   0,   0, 128, 
      5,   0,   0,   3,   0,   0, 
      7, 128,   0,   0, 228, 128, 
      9,   0, 228, 160,   6,   0, 
      0,   2,   1,   0,   1, 128, 
      8,   0, 255, 160,   5,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 255, 128,   1,   0, 
      0, 128,   4,   0,   0,   4, 
      0,   0,   8, 128,   0,   0, 
    255, 128,   0,   0, 255, 129, 
      0,   0,  85, 160,  11,   0, 
      0,   3,   1,   0,   1, 128, 
      0,   0, 255, 128,   0,   0, 
    170, 160,   5,   0,   0,   3, 
      0,   8,   7, 128,   0,   0, 
    228, 128,   1,   0,   0, 128, 
      1,   0,   0,   2,   0,   8, 
      8, 128,   0,   0,  85, 160, 
    255, 255,   0,   0
};
