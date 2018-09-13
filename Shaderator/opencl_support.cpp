#include "opencl_support.h"
#include "cpp_include.h"

std::mutex g_thread_descriptions_mutex;
std::map<std::thread::id, ThreadDescription> g_thread_descriptions;


void barrier(int type)
{
  GroupMemoryBarrierWithGroupSync();
}

int sub_group_reduce_add(int value)
{
  throw std::logic_error("Not implemented!");
}

int sub_group_scan_exclusive_add(int value)
{
  throw std::logic_error("Not implemented!");
}

int get_global_id(int i)
{
  std::thread::id this_thread_id = std::this_thread::get_id();
  bool found = false;
  while (!found) {
    {
      std::lock_guard<std::mutex> lock(g_thread_descriptions_mutex);
      found = g_thread_descriptions.find(this_thread_id) != g_thread_descriptions.end();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::lock_guard<std::mutex> lock(g_thread_descriptions_mutex);
  return g_thread_descriptions[this_thread_id].global_group_id[i];
}

int get_local_id(int i)
{
  std::thread::id this_thread_id = std::this_thread::get_id();
  bool found = false;
  while (!found) {
    {
      std::lock_guard<std::mutex> lock(g_thread_descriptions_mutex);
      found = g_thread_descriptions.find(this_thread_id) != g_thread_descriptions.end();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::lock_guard<std::mutex> lock(g_thread_descriptions_mutex);
  return g_thread_descriptions[this_thread_id].local_thread_id[i];
}

void set_thread_description(const std::thread::id& thread_id, const ThreadDescription& desc)
{
  std::lock_guard<std::mutex> lock(g_thread_descriptions_mutex);
  g_thread_descriptions[thread_id] = desc;
}
