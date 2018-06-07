#include "pch.h"

#include "basic_compute_executor.h"
#include "basic_compute_structured_buffer.hlsl"
#include "Engine.h"


void ClearGroupShareds()
{
  // no groupshared variables to clean
}

void BasicComputeExecutor::SetBuffer0(const StructuredBuffer<BufType>& buffer)
{
  Buffer0 = buffer;
  Buffer0.reset_access_counts();
}

void BasicComputeExecutor::SetBuffer1(const StructuredBuffer<BufType>& buffer)
{
  Buffer1 = buffer;
  Buffer1.reset_access_counts();
}

void BasicComputeExecutor::CreateOutput(uint size)
{
  BufferOut = RWStructuredBuffer<BufType>(size);
}

void BasicComputeExecutor::SetNumThreads(uint3 num_threads)
{
  num_threads_ = num_threads;
}

void BasicComputeExecutor::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
  Shaderator::Engine engine(CSMain, ClearGroupShareds, num_threads_);
  engine.Dispatch(x, y, z);
}

const RWStructuredBuffer<BufType>& BasicComputeExecutor::GetBufferOut()
{
  return BufferOut;
}
