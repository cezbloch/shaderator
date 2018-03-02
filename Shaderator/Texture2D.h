#pragma once

#include <vector>
#include "shader_types.h"

template<class T>
class Texture2D
{
public:
  Texture2D() = default;
  Texture2D(unsigned int _width, unsigned int _height);
  T& operator [](uint2 coordinates);
  T& Load(uint3 coordinates);
  const void* data();

private:
  unsigned int m_width;
  unsigned int m_height;
  std::vector<T> m_data;
};