#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"
#include <vector>
#include "bitonic_sort_executor.h"
#include "shader_types.h"

using UINT = unsigned int;

const UINT NUM_ELEMENTS = 512 * 16;
const UINT BITONIC_BLOCK_SIZE = 512;
const UINT TRANSPOSE_BLOCK_SIZE = 16;
const UINT MATRIX_WIDTH = BITONIC_BLOCK_SIZE;
const UINT MATRIX_HEIGHT = NUM_ELEMENTS / BITONIC_BLOCK_SIZE;

class Fixture
{
public:
  Fixture()
    : data(CreateBuffer(NUM_ELEMENTS))
    , results(CreateBuffer(NUM_ELEMENTS))
  {
    unsigned int level = 2;
    cpuShader.SetConstants(level, level, MATRIX_HEIGHT, MATRIX_WIDTH);

    cpuShader.SetUnorderedAccessViews0(data);
  }

  CSSortExecutor cpuShader;
  std::vector<UINT> data;
  std::vector<UINT> results;
};

TEST(BitonicSortGoogleTests, test_nothing)
{
  Fixture fixture;

  fixture.cpuShader.RunBitonicSortKernel(uint3(), uint3(), uint3(), 0);

  EXPECT_EQ(fixture.data[0], unsigned int(0));
}
