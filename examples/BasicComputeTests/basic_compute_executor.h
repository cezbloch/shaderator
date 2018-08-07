#pragma once

#include <vector>
//#define TRACE_ACCESS
#include "shaderator.h"
#include "shared_types.h"


class BasicComputeExecutor
{
public:
  void SetBuffer0(const StructuredBuffer<BufType>& buffer);
  void SetBuffer1(const StructuredBuffer<BufType>& buffer);
  void CreateOutput(uint size);
  void SetNumThreads(uint3 num_threads);
  void Dispatch(unsigned int x, unsigned int y, unsigned int z);
  const RWStructuredBuffer<BufType>& GetBufferOut();

private:
  uint3 num_threads_{1, 1, 1};
};
