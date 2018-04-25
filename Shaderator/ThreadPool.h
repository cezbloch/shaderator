#pragma once

#include "shader_types.h"
#include <functional>
#include <thread>
#include <queue>
#include <mutex>

using ShaderKernel = std::function<void(uint3, uint3, uint3, uint)>;

struct KernelArguments
{
  uint3 dispatchThreadID;
  uint3 groupID;
  uint3 groupThreadID;
  uint threadIndex;
};

void someWork() {}

class ThreadPool
{
public:
  ThreadPool(ShaderKernel kernel, unsigned int threadsAmount)
    : m_threadsAmount(threadsAmount)
    , m_shader(kernel)
  {
    for (uint i = 0; i < m_threadsAmount; ++i)
    {
      m_threads.push_back(std::thread(&ThreadPool::doWork, this));
    }
  }
  
  ~ThreadPool()
  {
    // wait for the queue to be empty - change this to wait for 
    while (!m_argumentsQueue.empty()) {

    }


    // instead of exit I can notify all threads of exiting
    m_exit = true;
    for (auto& thread : m_threads)
    {
      thread.join();
    }
  }
  
  void addTask(KernelArguments task) 
  {
    std::lock_guard<std::mutex> lock(m_queueLock);
    m_argumentsQueue.emplace(task);
    // here I can notify the worker thread that the state of queue has changed
  }

private:

  void doWork()
  {
    while (!m_exit) 
    {
      // here I can wait for notification from the parent thread
      std::lock_guard<std::mutex> lock(m_queueLock);
      if (!m_argumentsQueue.empty())
      {
        auto shaderArguments = m_argumentsQueue.front();
        m_argumentsQueue.pop();
        // notify  that element has been removed or that queue is empty so that destructor does not have to poll
        m_shader(shaderArguments.dispatchThreadID, shaderArguments.groupID, shaderArguments.groupThreadID, shaderArguments.threadIndex);
      }
    }
  }

  unsigned int m_threadsAmount = 0;
  bool m_exit = false;
  ShaderKernel m_shader;
  std::vector<std::thread> m_threads;
  std::mutex m_queueLock;
  std::queue<KernelArguments> m_argumentsQueue;
};