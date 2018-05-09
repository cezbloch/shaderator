#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>


template<class T>
class threadsafe_queue
{
public:
  threadsafe_queue() = default;
  threadsafe_queue& operator=(const threadsafe_queue&) = delete;
  threadsafe_queue(const threadsafe_queue& other)
  {
    std::lock_guard<std::mutex> lock(other.m_mutex);
    m_queue = other.m_queue;
  }

  void push(T t)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(t);
    m_elementAdded.notify_one();
  }

  //void push(T&& t)
  //{
  //  std::lock_guard<std::mutex> lock;
  //  m_queue.push_back(std::move(t));
  //}

  bool try_pop(T& t)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_queue.empty())
    {
      t = m_queue.front();
      m_queue.pop();
      return true;
    }

    return false;
  }

  void wait_and_pop(T& t)
  {
    std::unique_lock<std::mutex> lock(m_mutex);

    m_elementAdded.wait(lock, [this] { return !m_queue.empty(); });
    t = m_queue.front();
    m_queue.pop();
  }

  bool empty()
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
  }

private:
  std::queue<T> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_elementAdded;
};