#pragma once

#include <mutex>
#include <map>
#include "windows.h"
#include "opencl_types.h"

#define __global
#define __kernel
#define __constant //const
#define __private
#define __local

#define CLK_LOCAL_MEM_FENCE 1
#define CLK_GLOBAL_MEM_FENCE 2

template<typename T>
void atomic_or(T* dest, T value)
{
  InterlockedOr(reinterpret_cast<long*>(dest), value);
}


template<typename T>
void atomic_and(T* dest, T value)
{
  InterlockedAnd(reinterpret_cast<long*>(dest), value);
}

void barrier(int type);
int sub_group_reduce_add(int value);
int sub_group_scan_exclusive_add(int value);

struct ThreadDescription
{
  uint3 global_group_id;
  uint3 global_thread_id;
  uint global_thread_index;
  uint3 local_thread_id;
};

int get_global_id(int i);
int get_local_id(int i);

void set_thread_description(const std::thread::id&, const ThreadDescription&);