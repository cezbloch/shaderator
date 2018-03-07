#include "CppUnitTest.h"
#include <vector>
#include "glsl_include.h"

namespace ray_tracer 
{
#include "ray_tracer.glsl"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace glm {
  template<typename T, qualifier Q>
  GLM_FUNC_DECL std::wstring ToString(vec<4, T, Q> const& v)
  {
    return std::wstring();
  }
}

namespace GlslrRayTracerUnitTests
{
  TEST_CLASS(RayTracerShaderTests)
  {
  public:

    TEST_METHOD(TestRayAtOrigin)
    {
      gl_GlobalInvocationID = ivec3(0, 0, 0);

      ray_tracer::main();
      
      Assert::AreEqual(ray_tracer::img_output.pixel, vec4(0.0, 0.0, 0.0, 1.0));
    }
  };
}