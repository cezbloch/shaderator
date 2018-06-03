#include "basic_compute_executor.h"
#include "BasicCompute11_StructuredBuffer.hlsl"
#include "Engine.h"

template<class T>
std::vector<T> CreateBuffer(unsigned int num_elements)
{
  std::vector<T> buffer(num_elements);
  // initialize to 0xFF so that logic errors pop up quickly
  memset(&buffer[0], 0xFF, num_elements * sizeof T);

  return buffer;
}


void ClearGroupShareds()
{
  // no groupshared variables to clean
}

void BasicComputeExecutor::SetBuffer0(const StructuredBuffer<BufType>& buffer)
{
  Buffer0 = buffer;
}

void BasicComputeExecutor::SetBuffer1(const StructuredBuffer<BufType>& buffer)
{
  Buffer1 = buffer;
}

void BasicComputeExecutor::CreateOutput(uint size)
{
  BufferOut = CreateBuffer<BufType>(size);
}

void BasicComputeExecutor::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
  uint3 NumThreads(1, 1, 1);
  Shaderator::Engine engine(CSMain, ClearGroupShareds, NumThreads);
  engine.Dispatch(x, y, z);
}

const std::vector<BufType>& BasicComputeExecutor::GetBufferOut()
{
  return BufferOut;
}
