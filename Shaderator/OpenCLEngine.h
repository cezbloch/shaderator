#pragma once

#pragma once
#include "shader_types.h"
#include <functional>
#include "cpp_include.h"
#include <thread>
#include <vector>

typedef std::function<void()> ClearGroupSharedVariables;


namespace Shaderator { namespace OpenCL {

  template<typename... Args>
  class Engine
  {
  public:
    using Kernel = std::function<void(Args...)>;

    Engine::Engine(Kernel main, ClearGroupSharedVariables clear_function, uint3 numThreads)
      : m_main(main)
      , m_clear_groupshared_variables(clear_function)
      , m_numThreads(numThreads)
    {
      SetNumThreads(numThreads);
    }

    void Dispatch(uint x_size, uint y_size, uint z_size, Args... args)
    {
      for (uint z = 0; z < z_size; ++z) {
        for (uint y = 0; y < y_size; ++y) {
          for (uint x = 0; x < x_size; ++x) {
            uint3 groupID(x, y, z);
            run_thread_group(groupID, args...);
          }
        }
      }
    }

  private:
    void run_thread_group(uint3 groupID, Args... args)
    {
      m_clear_groupshared_variables();

      std::vector<std::thread> groupThreads;
      for (uint z = 0; z < m_numThreads.z; ++z) {
        for (uint y = 0; y < m_numThreads.y; ++y) {
          for (uint x = 0; x < m_numThreads.x; ++x) {
            uint3 groupThreadID(x, y, z);
            uint3 dispatchThreadID(groupID * m_numThreads + groupThreadID);
            uint threadIndex(m_numThreads.x * m_numThreads.y * z + m_numThreads.x * y + x);
            groupThreads.push_back(std::thread(m_main, args...));
            //groupThreads.push_back(std::thread(m_main, std::forward<Args...>(args...)));
          }
        }
      }

      for (auto& thread : groupThreads) {
        thread.join();
      }
    }

    Kernel m_main;
    ClearGroupSharedVariables m_clear_groupshared_variables;
    uint3 m_numThreads;
  };
}}

typedef std::function<void(uint3, uint3, uint3, uint)> ShaderKernel;
typedef std::function<void(int4 *, const uint, const uint, const uint)> BitonicSortKernel;

template class Shaderator::OpenCL::Engine<ShaderKernel>;
template class Shaderator::OpenCL::Engine<BitonicSortKernel>;
