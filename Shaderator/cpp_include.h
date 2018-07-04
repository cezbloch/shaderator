#pragma once

#ifdef __cplusplus

#include "shader_types.h"
#include "texture_2d.h"

#define groupshared
#ifdef TRACE_ACCESS
#define RWStructuredBuffer Texture2D
#define StructuredBuffer Texture2D
#else
#define RWStructuredBuffer std::vector
#define StructuredBuffer std::vector
#endif

// CBuffer
#define SHADERETOR_CBUFFER(name, constant_buffer_number)
#define SHADER_OPEN 
#define SHADER_CLOSE 

// StructruredBuffer
#define SHADERATOR_REGISTER_T(name, buffer_number) name;

// Unordered Access View
#define SHADERATOR_REGISTER_U(name, buffer_number) name;

// HLSL Tag wrappers
#define SHADERATOR_NUM_THREADS(x, y, z)
#define SHADERATOR_SV_GroupIndex(groupIndex) uint groupIndex
#define SHADERATOR_SV_DispatchThreadID(dispatchId) uint3 dispatchId
#define SHADERATOR_SV_GroupThreadID(groupThreadId) uint3 groupThreadId
#define SHADERATOR_SV_GroupID(groupID) uint3 groupID
#define SHADERATOR_LOOP 
#define SHADERATOR_UNROLL

//#define SHADERATOR_COPY_ARRAY(destination, source) std::copy(std::begin(source), std::end(source), std::begin(destination));
//#define SHADERATOR_ARRAY(type, name, size) std::array<type, size> name

// HLSL functions wrappers
void ShaderInterlockedOr(int& dest, int value);
void ShaderInterlockedAnd(int& dest, int value);

// HLSL functions
void GroupMemoryBarrierWithGroupSync();
int sign(int value);
float sign(float value);
float3 operator*(float3 v1, int3 v2);
uint3 operator*(float3 v1, uint3 v2);
uint3 operator&(uint3 v1, uint3 v2);
int4 operator<(int4 v1, int4 v2);

void ShaderAssert(bool expression);

// C++ specific
void SetNumThreads(uint3 numThreads);

#endif
