#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"
#include "glsl_include.h"

namespace ray_tracer
{
#include "ray_tracer.glsl"
}


TEST(GlslRayTracer, produces_black_pixel_at_0_0_0_position)
{
  gl_GlobalInvocationID = ivec3(0, 0, 0);

  ray_tracer::main();

  EXPECT_EQ(ray_tracer::img_output.pixel, vec4(0.0, 0.0, 0.0, 1.0));
}