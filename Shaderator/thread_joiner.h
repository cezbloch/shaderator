#pragma once


#include <thread>
#include <vector>

class thread_joiner
{
  std::vector<std::thread>& threads;

public:
  explicit thread_joiner(std::vector<std::thread>& threads_) :
    threads(threads_)
  {}

  ~thread_joiner()
  {
    for (unsigned long i = 0; i<threads.size(); ++i)
    {
      if (threads[i].joinable())
        threads[i].join();
    }
  }
};