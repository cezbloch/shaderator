#include "Engine.h"
#include "cpp_include.h"
#include <thread>

Shaderator::Engine::Engine(ShaderKernel main, ClearGroupSharedVariables clear_function, uint3 numThreads) :
    m_main(main)
  , m_clear_groupshared_variables(clear_function)
  , m_numThreads(numThreads)
{
  SetNumThreads(numThreads);
}

void Shaderator::Engine::run_thread_group(uint3 groupID)
{
  m_clear_groupshared_variables();

  std::vector<std::thread> groupThreads;
  for (uint z = 0; z < m_numThreads.z; ++z) {
    for (uint y = 0; y < m_numThreads.y; ++y) {
      for (uint x = 0; x < m_numThreads.x; ++x) {
        uint3 groupThreadID(x, y, z);
        uint3 dispatchThreadID(groupID * m_numThreads + groupThreadID);
        uint threadIndex(m_numThreads.x * m_numThreads.y * z + m_numThreads.x * y + x);

        groupThreads.push_back(std::thread(m_main, dispatchThreadID, groupID, groupThreadID, threadIndex));
      }
    }
  }

  for (auto& thread : groupThreads) {
    thread.join();
  }
}

void Shaderator::Engine::Dispatch(uint x_size, uint y_size, uint z_size)
{
  for (uint z = 0; z < z_size; ++z) {
    for (uint y = 0; y < y_size; ++y) {
      for (uint x = 0; x < x_size; ++x) {
        uint3 groupID(x, y, z);
        run_thread_group(groupID);
      }
    }
  }
}
