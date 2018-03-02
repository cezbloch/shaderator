#include "Texture2D.h"

template<class T>
inline Texture2D<T>::Texture2D(unsigned int _width, unsigned int _height) :
  m_width(_width),
  m_height(_height),
  m_data(_width * _height, T(0))
{}

template<class T>
inline T& Texture2D<T>::operator [](uint2 coordinates) {
  return Load(uint3(coordinates.x, coordinates.y, 0));
}

template<class T>
T& Texture2D<T>::Load(uint3 coordinates) {
  T& element = m_data[coordinates.y * m_width + coordinates.x];
  return element;
}

template<class T>
const void* Texture2D<T>::data()
{
  return reinterpret_cast<byte*>(m_data.data());
}