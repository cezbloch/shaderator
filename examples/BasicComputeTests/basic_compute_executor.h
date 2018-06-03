#pragma once

#include <vector>
#include "shader_types.h"
#include "shared_types.h"

class BasicComputeExecutor
{
public:
  void SetBuffer0(const StructuredBuffer<BufType>& buffer);
  void SetBuffer1(const StructuredBuffer<BufType>& buffer);
  void CreateOutput(uint size);

  void Dispatch(unsigned int x, unsigned int y, unsigned int z);

  const std::vector<BufType>& GetBufferOut();
};
