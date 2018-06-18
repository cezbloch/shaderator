#include "texture_2d.h"

template<class T>
inline Texture2D<T>::Texture2D(uint2 size)
  : size_(size)
  //, data_(size_.x * size_.y, Element<T>())
  , data_(size_.x * size_.y, T())
  , access_counts_(size_.x * size_.y, 0)
{}

template<class T>
inline Texture2D<T>::Texture2D(unsigned int width, unsigned int height) : Texture2D<T>(uint2(width, height))
{}

template<class T>
inline T& Texture2D<T>::operator [](uint2 coordinates) {
  return Load(uint3(coordinates.x, coordinates.y, 0));
}

template<class T>
T& Texture2D<T>::Load(uint3 coordinates) {
  auto index = coordinates.y * size_.x + coordinates.x;
  return at(index);
}

template<class T>
const void* Texture2D<T>::data()
{
  return data_.data();
}

template<class T>
const uint2 Texture2D<T>::size()
{
  return size_;
}

template class Texture2D<float4>;
template class Texture2D<uint4>;
template class Texture2D<int4>;