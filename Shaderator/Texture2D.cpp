#include "Texture2D.h"

template<class T>
inline Texture2D<T>::Texture2D(uint2 size) :
  m_size(size),
  m_data(m_size.x * m_size.y, T(0))
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
  T& element = m_data[coordinates.y * m_size.x + coordinates.x];
  return element;
}

template<class T>
const void* Texture2D<T>::data()
{
  return m_data.data();
}

template<class T>
const uint2 Texture2D<T>::size()
{
  return m_size;
}

template class Texture2D<float4>;
template class Texture2D<uint4>;
template class Texture2D<int4>;