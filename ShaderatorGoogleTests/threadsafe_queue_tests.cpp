#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"

#include "threadsafe_queue.h"
#include <vector>


TEST(ThreadSafeQueue, is_empty)
{
  threadsafe_queue<int> queue;

  EXPECT_TRUE(queue.empty());
}

TEST(ThreadSafeQueue, succeeds_pop_a_value)
{
  threadsafe_queue<int> queue;
  queue.push(1);
  int val = 0;

  EXPECT_TRUE(queue.try_pop(val));
  EXPECT_EQ(val, 1);
}

TEST(ThreadSafeQueue, fails_to_pop_a_value_from_empty_queue)
{
  threadsafe_queue<int> queue;
  int val = 0;

  EXPECT_FALSE(queue.try_pop(val));
}

TEST(ThreadSafeQueue, pops_after_waiting)
{
  threadsafe_queue<int> queue;
  int val = 0;

  auto add_element = [&queue]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    std::this_thread::yield();
    queue.push(1);
  };

  std::thread thread(add_element);

  queue.wait_and_pop(val);

  thread.join();
  EXPECT_EQ(val, 1);
}