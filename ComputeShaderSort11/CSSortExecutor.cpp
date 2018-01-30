#include "CSSortExecutor.h"
#include "ComputeShaderSort11.hlsl"
#include "Engine.h"

void ClearGroupShareds()
{
  memset(&shared_data, 0, sizeof(shared_data));
  memset(&transpose_shared_data, 0, sizeof(transpose_shared_data));
}


void CSSortExecutor::SetShaderResources0(std::vector<unsigned int>& buffer)
{
  m_shader_resource_0 = &buffer;
  Input.swap(buffer);
}

void CSSortExecutor::SetUnorderedAccessViews0(std::vector<unsigned int>& buffer)
{
  m_uav_0 = &buffer;
  Data.swap(buffer);
}

void CSSortExecutor::UpdateSubresource(std::vector<unsigned int>& buffer, const void *pSrcData, unsigned int size)
{
  const unsigned int* srcData = static_cast<const unsigned int*>(pSrcData);
  assert(size <= buffer.size());
  memcpy(&buffer[0], srcData, size * sizeof(unsigned int));
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

std::vector<unsigned int> CreateBuffer(unsigned int num_elements)
{
  std::vector<unsigned int> buffer(num_elements);
  memset(&buffer[0], 0, num_elements* sizeof(unsigned int));

  return buffer;
}