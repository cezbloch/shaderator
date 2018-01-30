#pragma once
#include "shader_types.h"
#include <functional>

typedef std::function<void(uint3, uint3, uint3, uint)> ShaderKernel;
typedef std::function<void()> ClearGroupSharedVariables;

namespace Shaderator {

  class Engine
  {
  public:
    explicit Engine(ShaderKernel main, ClearGroupSharedVariables clear_function, uint3 numThreads);

    void Dispatch(uint x, uint y, uint z);

  private:
    void run_thread_group(uint3 groupId);

    ShaderKernel m_main;
    ClearGroupSharedVariables m_clear_groupshared_variables;
    uint3 m_numThreads;
  };
}