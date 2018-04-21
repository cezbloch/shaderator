#include "stdafx.h"
#include "CppUnitTest.h"

#include <Barrier.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShaderatorUnitTests
{		
	TEST_CLASS(BarrierTests)
	{
	public:

		TEST_METHOD(TestBarrier)
		{
      int barrier_size = 32;
      Barrier barrier(barrier_size);
      int beforeBarrier = 0;
      int afterBarrier = 0;


      auto use_barrier = [&]() {
        beforeBarrier++;
        barrier.Wait();
        afterBarrier++;
      };
      
      std::vector<std::thread> threads;

      for (int i = 0; i < barrier_size; ++i) {
        threads.push_back(std::thread(use_barrier));
      }

      for (auto&& thread : threads) {
        thread.join();
      }
		}

	};
}