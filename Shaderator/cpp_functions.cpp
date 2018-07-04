#include "cpp_include.h"
#include "Barrier.h"
#include "windows.h"


static std::unique_ptr<Barrier> g_GroupMemoryBarrierWithGroupSync;

void ShaderInterlockedOr(int& dest, int value) 
{ 
  InterlockedOr(reinterpret_cast<long*>(&dest), value); 
}

void ShaderInterlockedAnd(int& dest, int value) 
{ 
  InterlockedAnd(reinterpret_cast<long*>(&dest), value); 
}

void ShaderAssert(bool expression) 
{ 
  assert(expression); 
}

void SetNumThreads(uint3 numThreads)
{
  g_GroupMemoryBarrierWithGroupSync.reset(new Barrier(numThreads.x * numThreads.y * numThreads.z));
}

void GroupMemoryBarrierWithGroupSync()
{
  g_GroupMemoryBarrierWithGroupSync->Wait();
};

int sign(int value)
{
  if (value == 0) {
    return 0;
  } else if (value > 0) {
    return 1;
  }

  return -1;
}

float sign(float value)
{
  if (value == 0.0) { 
    return 0.0;
  } else if (value > 0.0) {
    return 1.0;
  }

  return -1.0;
}

float3 operator*(float3 v1, int3 v2)
{
  float3 result(v1);
  result.x *= v2.x;
  result.y *= v2.y;
  result.z *= v2.z;
  return result;
}

uint3 operator*(float3 v1, uint3 v2)
{
  uint3 result(0, 0, 0);
  result.x *= static_cast<uint>(v1.x * v2.x);
  result.y *= static_cast<uint>(v1.y * v2.y);
  result.z *= static_cast<uint>(v1.z * v2.z);
  return result;
}

uint3 operator&(uint3 v1, uint3 v2)
{
  uint3 result(v1);
  result.x &= v2.x;
  result.y &= v2.y;
  result.z &= v2.z;
  return result;
}

int4 operator<(int4 v1, int4 v2)
{
  int4 result;
  result.x = v1.x < v2.x;
  result.y = v1.y < v2.y;
  result.z = v1.z < v2.z;
  result.w = v1.w < v2.w;
  return result;
}

//template<typename T>
//uint asuint(T t)
//{
//  return static_cast<uint>(t);
//}
//
//template<typename T>
//int asint(T t)
//{
//  return static_cast<int>(t);
//}
//
//template<typename T>
//float asfloat(T t)
//{
//  return static_cast<float>(t);
//}