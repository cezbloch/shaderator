#pragma once

#include "shader_types.h"
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
    while (!m_argumentsQueue.empty()) 
    {
      std::this_thread::yield();
    }

    m_exit = true;

    for (auto& thread : m_threads)
    {
      if (thread.joinable())
      {
        thread.join();
      }
    }
  }
  
  void addTask(KernelArguments task) 
  {
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_argumentsQueue.emplace(task);
    m_taskAvailable.notify_one();
  }

private:

  void doWork()
  {
    while (!m_exit) 
    {
      std::unique_lock<std::mutex> lock(m_queueMutex);
      m_taskAvailable.wait(lock, [&] { return !m_argumentsQueue.empty() || m_exit; });
      if (!m_argumentsQueue.empty())
      {
        auto shaderArguments = m_argumentsQueue.front();
        m_argumentsQueue.pop();
        lock.unlock();
        m_shader(shaderArguments.dispatchThreadID, shaderArguments.groupID, shaderArguments.groupThreadID, shaderArguments.threadIndex);
      }
    }
  }

  unsigned int m_threadsAmount = 0;
  std::atomic_bool m_exit = false;
  ShaderKernel m_shader;
  std::vector<std::thread> m_threads;
  std::mutex m_queueMutex;
  std::condition_variable m_queueEmpty;
  std::condition_variable m_taskAvailable;
  std::queue<KernelArguments> m_argumentsQueue;
};