#include "bitonic_sort_executor.h"
#include "ComputeShaderSort11.hlsl"
#include "Engine.h"


void ClearGroupShareds()
{
  for (int i = 0; i < BITONIC_BLOCK_SIZE; i++) {
    shared_data[i] = 0;
  }

  for (int i = 0; i < TRANSPOSE_BLOCK_SIZE * TRANSPOSE_BLOCK_SIZE; i++) {
    transpose_shared_data[i] = 0;
  }
}


void CSSortExecutor::SetShaderResources0(StructuredBuffer<unsigned int>& buffer)
{
  m_shader_resource_0 = &buffer;
  Input.swap(buffer);
}

void CSSortExecutor::SetUnorderedAccessViews0(RWStructuredBuffer<unsigned int>& buffer)
{
  m_uav_0 = &buffer;
  Data.swap(buffer);
}

void CSSortExecutor::InitializeGroupShareds()
{
  shared_data = StructuredBuffer<unsigned int>(BITONIC_BLOCK_SIZE);
  transpose_shared_data = StructuredBuffer<unsigned int>(TRANSPOSE_BLOCK_SIZE * TRANSPOSE_BLOCK_SIZE);
}

void CSSortExecutor::UpdateSubresource(StructuredBuffer<unsigned int>& buffer, const std::vector<uint>& srcData)
{
  assert(srcData.size() <= buffer.length());
  for (int i = 0; i < buffer.length(); i++) {
    auto value = srcData[i];
    auto& element = buffer[i];
    element = value;
    buffer[i] = srcData[i];
  }
}

void CSSortExecutor::SetConstants(unsigned int iLevel, unsigned int iLevelMask, unsigned int iWidth, unsigned int iHeight)
{
  g_iLevel = iLevel;
  g_iLevelMask = iLevelMask;
  g_iWidth = iWidth;
  g_iHeight = iHeight;
}

void CSSortExecutor::DispatchBitonicSort(unsigned int x, unsigned int y, unsigned int z)
{
  uint3 NumThreads(BITONIC_BLOCK_SIZE, 1, 1);
  Shaderator::Engine engine(BitonicSort, ClearGroupShareds, NumThreads);
  engine.Dispatch(x, y, z);
  restore_buffers();
}

void CSSortExecutor::DispatchMatrixTranspose(unsigned int x, unsigned int y, unsigned int z)
{
  uint3 NumThreads(TRANSPOSE_BLOCK_SIZE, TRANSPOSE_BLOCK_SIZE, 1);
  Shaderator::Engine engine(MatrixTranspose, ClearGroupShareds, NumThreads);
  engine.Dispatch(x, y, z);
  restore_buffers();
}

void CSSortExecutor::restore_buffers()
{
  if (m_uav_0) {
    m_uav_0->swap(Data);
  }

  if (m_shader_resource_0) {
    m_shader_resource_0->swap(Input);
  }
}

StructuredBuffer<uint> CreateBuffer(unsigned int num_elements)
{
  StructuredBuffer<uint> buffer(num_elements);
  for (int i = 0; i < num_elements; i++) {
    buffer[i] = 0;
  }

  return buffer;
}

void CSSortExecutor::RunBitonicSortKernel(uint3 dispatchThreadId, uint3 groupId, uint3 groupThreadId, uint groupIndex)
{
  SetNumThreads(uint3(1, 1, 1));
  BitonicSort(dispatchThreadId, groupId, groupThreadId, groupIndex);
  restore_buffers();
}