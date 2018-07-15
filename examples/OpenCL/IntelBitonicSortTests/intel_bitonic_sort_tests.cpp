#include "pch.h"
#include "intel_bitonic_sort_executor.h"
#include <iterator> //std::begin
#include <numeric> //std::itoa
#include <random>
#include <vector>

#define SAMPLE_CHECK_ERRORS

class Fixture
{
public:
  Fixture()
    : arraySize(1024)
    , data(arraySize)
  {
    std::iota(std::begin(data), std::end(data), 0); // Fill with 0, 1, ..., 99.
    std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
  }

  void ExecuteSortKernel(uint sortAscending)
  {
    int err = 0;
    int numStages = 0;
    uint temp;

    int stage;
    int passOfStage;

    for (temp = arraySize; temp > 2; temp >>= 1)
    {
      numStages++;
    }

    for (stage = 0; stage < numStages; stage++)
    {
      //err = clSetKernelArg(executable.kernel, 1, sizeof(uint), (void *)&stage);

      for (passOfStage = stage; passOfStage >= 0; passOfStage--)
      {
        //err = clSetKernelArg(executable.kernel, 2, sizeof(uint), (void *)&passOfStage);

        // set work-item dimensions
        size_t gsz = arraySize / (2 * 4);
        size_t global_work_size[1] = { passOfStage ? gsz : gsz << 1 };    //number of quad items in input array

        //err = clEnqueueNDRangeKernel(oclobjects.queue, executable.kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
        executor.Dispatch(global_work_size[0], 1, 1, reinterpret_cast<int4*>(data.data()), stage, passOfStage, sortAscending);
      }
    }
  }

  uint arraySize;
  std::vector<int> data;
  BasicComputeExecutor executor;
};

TEST(BasicComputeGoogleTests, test_can_execute_open_cl_bitonic_sort)
{
  Fixture fixture;

  fixture.ExecuteSortKernel(0);
}
