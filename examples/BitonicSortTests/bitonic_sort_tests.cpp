#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define TRACE_ACCESS

#include <algorithm> //std::sort, std::shuffle
#include <iterator> //std::begin
#include <numeric> //std::itoa
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "bitonic_sort_executor.h"
#include "shader_types.h"

using UINT = unsigned int;

const UINT BITONIC_BLOCK_SIZE = 16;
const UINT TRANSPOSE_BLOCK_SIZE = 16;
const UINT NUM_ELEMENTS = BITONIC_BLOCK_SIZE * TRANSPOSE_BLOCK_SIZE;
const UINT MATRIX_WIDTH = BITONIC_BLOCK_SIZE;
const UINT MATRIX_HEIGHT = NUM_ELEMENTS / BITONIC_BLOCK_SIZE;

class Fixture
{
public:
  Fixture()
    : data(NUM_ELEMENTS)
  {
    std::iota(std::begin(data), std::end(data), 0); // Fill with 0, 1, ..., 99.
    std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
  }

  void CPUShaderSort()
  {
    cpuShader.InitializeGroupShareds();
    // Upload the data
    cpuShader.UpdateSubresource(buffer1UAV, data);

    // Sort the data
    // First sort the rows for the levels <= to the block size
    for (UINT level = 2; level <= BITONIC_BLOCK_SIZE; level = level * 2)
    {
      cpuShader.SetConstants(level, level, MATRIX_HEIGHT, MATRIX_WIDTH);

      // Sort the row data
      cpuShader.SetUnorderedAccessViews0(buffer1UAV);
      cpuShader.DispatchBitonicSort(NUM_ELEMENTS / BITONIC_BLOCK_SIZE, 1, 1);
    }

    // Then sort the rows and columns for the levels > than the block size
    // Transpose. Sort the Columns. Transpose. Sort the Rows.
    for (UINT level = (BITONIC_BLOCK_SIZE * 2); level <= NUM_ELEMENTS; level = level * 2)
    {
      cpuShader.SetConstants((level / BITONIC_BLOCK_SIZE), (level & ~NUM_ELEMENTS) / BITONIC_BLOCK_SIZE, MATRIX_WIDTH, MATRIX_HEIGHT);

      // Transpose the data from buffer 1 into buffer 2
      cpuShader.SetUnorderedAccessViews0(buffer2UAV);
      cpuShader.SetShaderResources0(buffer1UAV);
      cpuShader.DispatchMatrixTranspose(MATRIX_WIDTH / TRANSPOSE_BLOCK_SIZE, MATRIX_HEIGHT / TRANSPOSE_BLOCK_SIZE, 1);

      // Sort the transposed column data
      cpuShader.SetUnorderedAccessViews0(buffer2UAV);
      cpuShader.SetShaderResources0(buffer1UAV);
      cpuShader.DispatchBitonicSort(NUM_ELEMENTS / BITONIC_BLOCK_SIZE, 1, 1);

      cpuShader.SetConstants(BITONIC_BLOCK_SIZE, level, MATRIX_HEIGHT, MATRIX_WIDTH);

      // Transpose the data from buffer 2 back into buffer 1
      cpuShader.SetUnorderedAccessViews0(buffer1UAV);
      cpuShader.SetShaderResources0(buffer2UAV);
      cpuShader.DispatchMatrixTranspose(MATRIX_HEIGHT / TRANSPOSE_BLOCK_SIZE, MATRIX_WIDTH / TRANSPOSE_BLOCK_SIZE, 1);

      // Sort the row data
      cpuShader.SetUnorderedAccessViews0(buffer1UAV);
      cpuShader.SetShaderResources0(buffer2UAV);
      cpuShader.DispatchBitonicSort(NUM_ELEMENTS / BITONIC_BLOCK_SIZE, 1, 1);
    }
  }

  void verify()
  {
    std::sort(data.begin(), data.end());

    bool are_shader_elements_sorted = true;
    for (UINT i = 0; i < NUM_ELEMENTS; ++i)
    {
      if (data[i] != buffer1UAV[i].get())
      {
        are_shader_elements_sorted = false;
        break;
      }
    }

    EXPECT_TRUE(are_shader_elements_sorted);
  }

  CSSortExecutor cpuShader;
  std::vector<uint> data;
  StructuredBuffer<uint> buffer1UAV = CreateBuffer(NUM_ELEMENTS);
  StructuredBuffer<uint> buffer2UAV = CreateBuffer(NUM_ELEMENTS);
};

TEST(BitonicSortGoogleTests, test_256_random_numbers_are_sorted)
{
  Fixture fixture;

  fixture.CPUShaderSort();

  fixture.verify();
}