#pragma once
#include <thread>
#include <condition_variable>
#include <memory>


class Barrier {
public:
  explicit Barrier(std::size_t iCount) :
    mThreshold(iCount),
    mCount(iCount),
    mGeneration(0) {
  }

  void Wait() {
    std::unique_lock<std::mutex> lLock{ mMutex };
    auto lGen = mGeneration;
    if (!--mCount) {
      mGeneration++;
      mCount = mThreshold;
      mCond.notify_all();
    }
    else {
      mCond.wait(lLock, [this, lGen] { return lGen != mGeneration; });
    }
  }

private:
  std::mutex mMutex;
  std::condition_variable mCond;
  std::size_t mThreshold;
  std::size_t mCount;
  std::size_t mGeneration;
};
