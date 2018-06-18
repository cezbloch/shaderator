#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"

#include "thread_pool.h"
#include <vector>

std::vector<int> g_values(10);

void SampleKernel(uint3, uint3, uint3, uint val)
{
  g_values[val - 1] = val * val;
}

void addTask(thread_pool& pool, uint val)
{
  KernelArguments args;
  args.threadIndex = val;
  pool.addTask(args);
}

TEST(ThreadPool, 32_treads_are_properly_blocked)
{
  {
    thread_pool pool(SampleKernel, 2);
    addTask(pool, 1);
    addTask(pool, 2);
    addTask(pool, 3);
    addTask(pool, 4);
    addTask(pool, 5);
    addTask(pool, 6);
    addTask(pool, 7);
  }

  EXPECT_EQ(g_values[6], 49);
}