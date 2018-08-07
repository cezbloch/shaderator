#pragma once

#include <vector>
#define TRACE_ACCESS
#include "shaderator.h"

class CSSortExecutor
{
public:
  void SetShaderResources0(StructuredBuffer<unsigned int>& buffer);
  void SetUnorderedAccessViews0(RWStructuredBuffer<unsigned int>& buffer);
  void InitializeGroupShareds();

  void UpdateSubresource(StructuredBuffer<unsigned int>& buffer, const std::vector<uint>& srcData);
  void SetConstants(unsigned int iLevel, unsigned int iLevelMask, unsigned int iWidth, unsigned int iHeight);

  void DispatchBitonicSort(unsigned int x, unsigned int y, unsigned int z);
  void DispatchMatrixTranspose(unsigned int x, unsigned int y, unsigned int z);

  void RunBitonicSortKernel(uint3 dispatchThreadId, uint3 groupId, uint3 groupThreadId, uint groupIndex);

private:
  void restore_buffers();

  StructuredBuffer<unsigned int>* m_shader_resource_0 = nullptr;
  StructuredBuffer<unsigned int>* m_uav_0 = nullptr;

};

StructuredBuffer<uint> CreateBuffer(unsigned int num_elements);