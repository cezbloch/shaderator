#include "pch.h"
#include "intel_bitonic_sort_executor.h"
#include <iterator> //std::begin
#include <numeric> //std::itoa
#include <random>
#include <vector>

class Fixture
{
public:
  Fixture()
    : arraySize(1024)
    , data(arraySize)
  {
    std::iota(std::begin(data), std::end(data), 0); // Fill with 0, 1, ..., 99.
    std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
    reference_data = data;
  }

  void ExecuteSortKernel(uint sortAscending)
  {
    int err = 0;
    int numStages = 0;
    uint temp;

    int stage;
    int passOfStage;

    for (temp = arraySize; temp > 2; temp >>= 1) {
      numStages++;
    }

    for (stage = 0; stage < numStages; stage++) {
      for (passOfStage = stage; passOfStage >= 0; passOfStage--) {
        // set work-item dimensions
        size_t gsz = arraySize / (2 * 4);
        size_t global_work_size[1] = { passOfStage ? gsz : gsz << 1 };    //number of quad items in input array

        executor.Dispatch(global_work_size[0], 1, 1, reinterpret_cast<int4*>(data.data()), stage, passOfStage, sortAscending);
      }
    }
  }

  void verify()
  {
    std::sort(reference_data.begin(), reference_data.end());
    bool is_equal = std::equal(data.begin(), data.end(), reference_data.begin());
    EXPECT_TRUE(is_equal);
  }

private:
  uint arraySize;
  std::vector<int> data;
  std::vector<int> reference_data;
  BasicComputeExecutor executor;
};

TEST(BasicComputeGoogleTests, test_can_execute_open_cl_bitonic_sort)
{
  Fixture fixture;
  uint sortAscending = 1;

  fixture.ExecuteSortKernel(sortAscending);

  fixture.verify();
}
