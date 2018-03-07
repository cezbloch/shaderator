#pragma once
#define GLM_FORCE_SWIZZLE // this is to enable vector swizzling ie. some_vector.rgb
#include <glm/glm.hpp>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

using namespace glm;

ivec3 gl_GlobalInvocationID;
#define in

#define layout(...)

#define uniform

class image2D
{
public:
  vec4 pixel;
};

ivec2 imageSize(const image2D& image) 
{ 
  return ivec2(1,1);
}

void imageStore(image2D& image, ivec2 pixel_coords, vec4 pixel)
{
  image.pixel = pixel;
}