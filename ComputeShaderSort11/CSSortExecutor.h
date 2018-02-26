#pragma once

#include <vector>
#include "shader_types.h"

class CSSortExecutor
{
public:
  void SetShaderResources0(std::vector<unsigned int>& buffer);
  void SetUnorderedAccessViews0(std::vector<unsigned int>& buffer);

  void UpdateSubresource(std::vector<unsigned int>& buffer, const void *pSrcData, unsigned int size);
  void SetConstants(unsigned int iLevel, unsigned int iLevelMask, unsigned int iWidth, unsigned int iHeight);

  void DispatchBitonicSort(unsigned int x, unsigned int y, unsigned int z);
  void DispatchMatrixTranspose(unsigned int x, unsigned int y, unsigned int z);

  void RunBitonicSortKernel(uint3 dispatchThreadId, uint3 groupId, uint3 groupThreadId, uint groupIndex);

private:
  void restore_buffers();

  std::vector<unsigned int>* m_shader_resource_0 = nullptr;
  std::vector<unsigned int>* m_uav_0 = nullptr;

};

std::vector<unsigned int> CreateBuffer(unsigned int num_elements);