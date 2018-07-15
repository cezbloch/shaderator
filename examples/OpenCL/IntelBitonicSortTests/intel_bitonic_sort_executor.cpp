#include "pch.h"

#include "intel_bitonic_sort_executor.h"

#define __global
#define __kernel

size_t get_global_id(size_t i) { return i; }

#include "BitonicSort.cl"
#include "OpenCLEngine.h"

void ClearGroupShareds(){};


void BasicComputeExecutor::Dispatch(unsigned int x, unsigned int y, unsigned int z,
  int4* theArray, const uint stage, const uint passOfStage, const uint dir)
{
  Shaderator::OpenCL::Engine<int4 *, const uint, const uint, const uint> engine(BitonicSort, ClearGroupShareds, num_threads_);
  engine.Dispatch(x, y, z, theArray, stage, passOfStage, dir);
}

