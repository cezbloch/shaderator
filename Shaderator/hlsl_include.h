#ifndef __cplusplus

#define SHADERETOR_CBUFFER(name, constant_buffer_number) cbuffer name : register(b ## constant_buffer_number)
#define SHADER_OPEN {
#define SHADER_CLOSE };

#define SHADERATOR_REGISTER_T(name, buffer_number) name : register(t ## buffer_number)
#define SHADERATOR_REGISTER_U(name, buffer_number) name : register(u ## buffer_number)
#define SHADERATOR_NUM_THREADS(x, y, z) [numthreads( x, y, z )]
#define SHADERATOR_SV_GroupIndex(groupIndex) uint groupIndex : SV_GroupIndex
#define SHADERATOR_SV_DispatchThreadID(dispatchId) uint3 dispatchId : SV_DispatchThreadID
#define SHADERATOR_SV_GroupThreadID(groupThreadId) uint3 groupThreadId : SV_GroupThreadID
#define SHADERATOR_SV_GroupID(groupID) uint3 groupID : SV_GroupID
#define SHADERATOR_LOOP [loop]
#define SHADERATOR_UNROLL [unroll]
//#define SHADERATOR_COPY_ARRAY(destination, source) destination = source
//#define SHADERATOR_ARRAY(type, name, size) type name[size]

#define ShaderInterlockedOr InterlockedOr
#define ShaderInterlockedAnd InterlockedAnd
//void ShaderAssert(bool expression) {}

#endif