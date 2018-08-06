#pragma once

#include <vector>
#include "shader_types.h"


template<class T>
class Element
{
public:
  Element<T>& operator=(const Element<T>& other)
  {
    if (this != &other)
    {
      write_count_++;
      value_ = other.value_;
    }

    return *this;
  }

  //unsigned int operator=(Element<T> t)
  //{
  //  return value_;
  //};

  Element<T>& operator=(const T& value)
  {
    write_count_++;
    value_ = value;

    return *this;
  }

  bool operator<=(const Element<T>& other)
  {
    return value_ <= other.value_;
  }

  void reset_count()
  {
    write_count_ = 0;
  }

  T& get()
  {
    return value_;
  }

  uint get_write_count()
  {
    return write_count_;
  }

private:
  T value_;
  uint write_count_ = 0;
};

template<class T>
class Texture2D
{
public:
  Texture2D() = default;

  Texture2D(unsigned int size)
    : size_(size, 1)
#ifdef USE_ELEMENT
    , data_(size, Element<T>())
#else
    , data_(size, T())
#endif
    , write_counts_(size, 0)
    , read_counts_(size, 0)
  {
  }

  Texture2D(unsigned int width, unsigned int height);
  Texture2D(uint2 size);

#ifdef USE_ELEMENT
  Element<T>& operator[](uint index)
#else
  T& operator[](uint index)
#endif
  {
    write_counts_[index]++;
    auto& element = data_[index];
    return element;
  }

  //const T& operator[](uint index) const
  //{
  //  read_counts_[index]++;
  //  return data_[index];
  //}

  T& at(uint index)
  {
#ifdef USE_ELEMENT
    T& element = data_[index];
#else
    T& element = data_[index];
#endif
    return element;
  }

  void swap(Texture2D<T>& other)
  {
    Texture2D<T> tmp;
    tmp.write_counts_ = this->write_counts_;
    tmp.data_ = this->data_;
    tmp.size_ = this->size_;
    tmp.read_counts_ = this->read_counts_;

    this->write_counts_ = other.write_counts_;
    this->data_ = other.data_;
    this->size_ = other.size_;
    this->read_counts_ = other.read_counts_;

    other.write_counts_ = tmp.write_counts_;
    other.data_ = tmp.data_;
    other.size_ = tmp.size_;
    other.read_counts_ = tmp.read_counts_;
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
    std::memset(&write_counts_[0], 0, (sizeof uint) * size_.x * size_.y);
#ifdef USE_ELEMENT
    for (auto& el : data_) {
      el.reset_count();
    }
#endif
  }

  uint get_write_count(uint index)
  {
#ifdef USE_ELEMENT
    return data_[index].get_write_count();
#else
    return write_counts_[index];
#endif
  }

private:
  uint2 size_;
#ifdef USE_ELEMENT
  std::vector<Element<T>> data_;
#else
  std::vector<T> data_;
#endif
  std::vector<uint> write_counts_;
  mutable std::vector<uint> read_counts_;
};
