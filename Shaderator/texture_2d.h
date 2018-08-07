#pragma once

#include <vector>
#include "shader_types.h"


template<class T>
class Texture2D
{
public:
  Texture2D() = default;

  Texture2D(unsigned int size)
    : size_(size, 1)
    , data_(size, T())
  {
  }

  Texture2D(uint2 size)
    : size_(size)
    , data_(size_.x * size_.y, T())
  {}

  Texture2D(unsigned int width, unsigned int height) : Texture2D<T>(uint2(width, height))
  {}

  T& operator[](uint index)
  {
    return at(index);
  }

  T& at(uint index)
  {
    return data_[index];
  }

  void swap(Texture2D<T>& other)
  {
    Texture2D<T> tmp;
    tmp.data_ = this->data_;
    tmp.size_ = this->size_;

    this->data_ = other.data_;
    this->size_ = other.size_;

    other.data_ = tmp.data_;
    other.size_ = tmp.size_;
  }

  T& [](uint2 coordinates) {
    return Load(uint3(coordinates.x, coordinates.y, 0));
  }

  T& Load(uint3 coordinates) {
    auto index = coordinates.y * size_.x + coordinates.x;
    return at(index);
  }

  const void* data()
  {
    return data_.data();
  }

  const uint2 size()
  {
    return size_;
  }

  const uint length() 
  {
    return size_.x * size_.y;
  }

private:
  uint2 size_;
  std::vector<T> data_;
};
