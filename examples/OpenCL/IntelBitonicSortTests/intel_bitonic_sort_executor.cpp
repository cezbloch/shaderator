#include "pch.h"

#include "intel_bitonic_sort_executor.h"

#define __global
#define __kernel

size_t get_global_id(size_t i) { return i; }

#include "BitonicSort.cl"
#include "Engine.h"



void BasicComputeExecutor::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
  //Shaderator::Engine engine(CSMain, ClearGroupShareds, num_threads_);
  //engine.Dispatch(x, y, z);
}

