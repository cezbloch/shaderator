#pragma once

#include <mutex>
#include <map>
#include "shader_types.h"

#define __global
#define __kernel

std::mutex g_threadIdsMutex;
std::map<std::thread::id, uint> g_threadIds;
size_t get_global_id(size_t i)
{
  std::thread::id this_id = std::this_thread::get_id();
  bool found = false;
  while (!found) {
    {
      std::lock_guard<std::mutex> lock(g_threadIdsMutex);
      found = g_threadIds.find(this_id) != g_threadIds.end();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::lock_guard<std::mutex> lock(g_threadIdsMutex);
  return g_threadIds[this_id];
}