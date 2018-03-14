#pragma once

#include <vector>
#include "shader_types.h"

template<class T>
class Texture2D
{
public:
  Texture2D() = default;
  Texture2D(unsigned int _width, unsigned int _height);
  Texture2D(uint2 size);
  T& operator [](uint2 coordinates);
  T& Load(uint3 coordinates);
  const void* data();
  const uint2 size();

private:
  uint2 m_size;
  std::vector<T> m_data;
};
