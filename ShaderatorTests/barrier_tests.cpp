#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"
#include <Barrier.h>
#include <vector>

TEST(BarrierTests, 32_treads_are_properly_blocked)
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