#pragma once

#include <vector>
#define TRACE_ACCESS
#include "shaderator.h"


class BasicComputeExecutor
{
public:
  void Dispatch(unsigned int x, unsigned int y, unsigned int z, int4 *, const uint, const uint, const uint);

private:
  uint3 num_threads_{1, 1, 1};
};
