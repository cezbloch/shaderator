#include "stdafx.h"
#include "CppUnitTest.h"

#include "threadsafe_queue.h"
#include <chrono>
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ShaderatorUnitTests
{
  TEST_CLASS(ThreadSafeQueueTests)
  {
  public:

    TEST_METHOD(is_empty)
    {
      threadsafe_queue<int> queue;

      Assert::IsTrue(queue.empty());
    }

    TEST_METHOD(succeeds_pop_a_value)
    {
      threadsafe_queue<int> queue;
      queue.push(1);
      int val = 0;

      Assert::IsTrue(queue.try_pop(val));
      Assert::AreEqual(val, 1);
    }

    TEST_METHOD(fails_to_pop_a_value_from_empty_queue)
    {
      threadsafe_queue<int> queue;
      int val = 0;

      Assert::IsFalse(queue.try_pop(val));
    }

    TEST_METHOD(pops_after_waiting)
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
      Assert::AreEqual(val, 1);
    }
  };
}