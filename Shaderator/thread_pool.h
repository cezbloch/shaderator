#pragma once

#include "shader_types.h"
#include "threadsafe_queue.h"
#include "thread_joiner.h"
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

using ShaderKernel = std::function<void(uint3, uint3, uint3, uint)>;

struct KernelArguments
{
  uint3 dispatchThreadID;
  uint3 groupID;
  uint3 groupThreadID;
  uint threadIndex;
};

class thread_pool
{
public:
  thread_pool(ShaderKernel kernel, unsigned int threadsAmount)
    : m_shader(kernel)
    , m_joiner(m_threads)
  {
    for (uint i = 0; i < threadsAmount; ++i)
    {
      m_threads.push_back(std::thread(&thread_pool::doWork, this));
    }
  }
  
  ~thread_pool()
  {
    while (!m_argumentsQueue.empty())
    {
      std::this_thread::yield();
    }

    m_exit = true;
  }
  
  void addTask(KernelArguments& task) 
  {
    m_argumentsQueue.push(task);
  }

private:

  void doWork()
  {
    KernelArguments shaderArguments;

    while (!m_exit) 
    {
      if (m_argumentsQueue.try_pop(shaderArguments))
      {
        m_shader(shaderArguments.dispatchThreadID, shaderArguments.groupID, shaderArguments.groupThreadID, shaderArguments.threadIndex);
      } else {
        std::this_thread::yield();
      }
    }
  }

  std::atomic_bool m_exit = false;
  ShaderKernel m_shader;
  std::vector<std::thread> m_threads;
  threadsafe_queue<KernelArguments> m_argumentsQueue;
  thread_joiner m_joiner;
};