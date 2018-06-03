#include "CppUnitTest.h"
#include <vector>
#include "basic_compute_executor.h"
#include "shader_types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ComputeShaderUnitTests
{
  class Fixture
  {
  public:
    Fixture()
      : buffer0(num_elements)
      , buffer1(num_elements)
    {
      for (int i = 0; i < num_elements; ++i)
      {
        buffer0[i].i = i;
        buffer0[i].f = static_cast<float>(2 * i);
        buffer1[i].i = i;
        buffer1[i].f = static_cast<float>(2 * i);
      }

      cpu_shader.SetBuffer0(buffer0);
      cpu_shader.SetBuffer1(buffer1);
      cpu_shader.CreateOutput(num_elements);
    }

    void verify_output()
    {
      auto buffer_out = cpu_shader.GetBufferOut();

      for (int i = 0; i < num_elements; ++i)
      {
        Assert::AreEqual(2 * i, buffer_out[i].i);
        Assert::AreEqual(static_cast<float>(4 * i), buffer_out[i].f);
      }
    }

    int num_elements = 16;
    BasicComputeExecutor cpu_shader;
    std::vector<BufType> buffer0;
    std::vector<BufType> buffer1;
    std::vector<BufType> bufferOut;
  };


	TEST_CLASS(BasicComputeTests)
	{
	public:

    TEST_METHOD(test_output_buffer_contains_sum_of_two_input_buffers)
    {
      // Arrange
      Fixture fixture;

      // Act
      fixture.cpu_shader.Dispatch(fixture.num_elements, 1, 1);

      // Assert
      fixture.verify_output();
    }
	};
}