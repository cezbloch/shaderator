#include "CppUnitTest.h"
#include <vector>
#include "CSSortExecutor.h"
#include "shader_types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using UINT = unsigned int;

namespace ComputeShaderUnitTests
{		
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


	TEST_CLASS(BitonicSortKernelTests)
	{
	public:
    //TEST_CLASS_INITIALIZE(ClassInitialize)
    //{
    //  
    //}

    //TEST_CLASS_CLEANUP(ClassCleanup)
    //{
    //  Logger::WriteMessage("In Class Cleanup");
    //}

    TEST_METHOD(TestBitonicSortEmptyInput)
    {
      // Arrange
      Fixture fixture;

      // Act
      fixture.cpuShader.RunBitonicSortKernel(uint3(), uint3(), uint3(), 0);

      // Assert
      Assert::AreEqual(fixture.data[0], unsigned int(0));
    }
	};
}