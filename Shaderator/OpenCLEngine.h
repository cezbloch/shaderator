#pragma once
#include "shader_types.h"
#include "opencl_support.h"
#include <functional>
#include <thread>
#include <vector>

typedef std::function<void()> ClearGroupSharedVariables;


namespace Shaderator { namespace OpenCL {

  template<typename... Args>
  class Engine
  {
  public:
    using Kernel = std::function<void(Args...)>;

    Engine::Engine(Kernel main, ClearGroupSharedVariables clear_function, uint3 numThreads)
      : kernel_(main)
      , clear_groupshared_variables_(clear_function)
      , threads_amount_in_group_(numThreads)
    {
      SetNumThreads(numThreads);
    }

    void Dispatch(uint x_size, uint y_size, uint z_size, Args... args)
    {
      for (uint z = 0; z < z_size; ++z) {
        for (uint y = 0; y < y_size; ++y) {
          for (uint x = 0; x < x_size; ++x) {
            uint3 groupID(x, y, z);
            run_thread_group(groupID, args...);
          }
        }
      }
    }

  private:
    void run_thread_group(uint3 global_group_id, Args... args)
    {
      clear_groupshared_variables_();

      std::vector<std::thread> group_threads;
      for (uint z = 0; z < threads_amount_in_group_.z; ++z) {
        for (uint y = 0; y < threads_amount_in_group_.y; ++y) {
          for (uint x = 0; x < threads_amount_in_group_.x; ++x) {

            uint3 local_thread_id (x, y, z);
            uint3 global_thread_id (global_group_id * threads_amount_in_group_ + local_thread_id);
            uint global_thread_index (threads_amount_in_group_.x * threads_amount_in_group_.y * z + threads_amount_in_group_.x * y + x);

            auto kernel_thread = std::thread(kernel_, args...);
            ThreadDescription desc{ global_group_id , global_thread_id, global_thread_index, local_thread_id };
            set_thread_description(kernel_thread.get_id(), desc);

            group_threads.push_back(std::move(kernel_thread));
          }
        }
      }

      for (auto& thread : group_threads) {
        thread.join();
      }
    }

    Kernel kernel_;
    ClearGroupSharedVariables clear_groupshared_variables_;
    uint3 threads_amount_in_group_;
  };
}}
