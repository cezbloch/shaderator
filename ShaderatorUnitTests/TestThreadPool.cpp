#include "stdafx.h"
#include "CppUnitTest.h"

#include "thread_pool.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::vector<int> g_values(10);

void SampleKernel(uint3, uint3, uint3, uint val)
{
  g_values[val - 1] = val * val;
}

namespace ShaderatorUnitTests
{
  TEST_CLASS(thread_pool_tests)
  {
  public:

    void addTask(thread_pool& pool, uint val)
    {
      KernelArguments args;
      args.threadIndex = val;
      pool.addTask(args);
    }

    TEST_METHOD(TestThreadPool)
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

      Assert::AreEqual(g_values[6], 49);
    }

  };
}