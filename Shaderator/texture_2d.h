#pragma once

#include <vector>
#include "shader_types.h"

template<class T>
class Element
{
public:
  Element & operator=(const Element& other)
  {
    if (this != &other)
    {
      write_count_++;
      value_ = other.value_;
    }

    return *this;
  }

  Element & operator=(const T& value)
  {
    if (this != &other)
    {
      write_count_++;
      value_ = value;
    }

    return *this;
  }

  T value_;
private:

  uint read_count_;
  uint write_count_;
};

template<class T>
class Texture2D
{
public:
  Texture2D() = default;

  Texture2D(unsigned int size)
    : size_(size, 1)
    , data_(size, T())
    //, data_(size, Element<T>())
    , access_counts_(size, 0)
  {
  }

  Texture2D(unsigned int width, unsigned int height);
  Texture2D(uint2 size);

  T& operator[](uint index)
  {
    return at(index);
  }

  T& at(uint index)
  {
    access_counts_[index]++;
    T& element = data_[index];
    //T& element = data_[index].value_;
    return element;
  }

  void swap(Texture2D<T>& other)
  {
    Texture2D<T> tmp;
    tmp.access_counts_ = this->access_counts_;
    tmp.data_ = this->data_;
    tmp.size_ = this->size_;

    this->access_counts_ = other.access_counts_;
    this->data_ = other.data_;
    this->size_ = other.size_;

    other.access_counts_ = tmp.access_counts_;
    other.data_ = tmp.data_;
    other.size_ = tmp.size_;
  }

  T& operator [](uint2 coordinates);
  T& Load(uint3 coordinates);
  const void* data();
  const uint2 size();
  const uint length() 
  {
    return size_.x * size_.y;
  }
  void reset_access_counts()
  {
    std::memset(&access_counts_[0], 0, (sizeof uint) * size_.x * size_.y);
  }

private:
  uint2 size_;
  std::vector<T> data_;
  //std::vector<Element<T>> data_;
  std::vector<uint> access_counts_;
};
