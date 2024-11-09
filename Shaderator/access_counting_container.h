#pragma once

#include <vector>
#include "shader_types.h"
#include "element.h"


template<class T>
class AccessCountingContainer
{
public:
  AccessCountingContainer() = default;

  AccessCountingContainer(unsigned int size)
    : AccessCountingContainer(uint2(size, 1))
  {
  }

  AccessCountingContainer(uint2 size)
    : size_(size)
    , data_(size_.x * size_.y, Element<T>())
    , access_counts_(size_.x * size_.y, 0)
    , read_counts_(size_.x * size_.y, 0)
  {
  }

  Element<T>& operator[](uint index)
  {
    return at(index);
  }

  Element<T>& operator [](uint2 coordinates)
  {
    return Load(uint3(coordinates.x, coordinates.y, 0));
  }

  Element<T>& Load(uint3 coordinates) {
    auto index = coordinates.y * size_.x + coordinates.x;
    return at(index);
  }

  Element<T>& at(uint index)
  {
    access_counts_[index]++;
    return data_[index];
  }

  void swap(AccessCountingContainer<T>& other)
  {
    AccessCountingContainer<T> tmp;
    tmp.access_counts_ = this->access_counts_;
    tmp.data_ = this->data_;
    tmp.size_ = this->size_;
    tmp.read_counts_ = this->read_counts_;

    this->access_counts_ = other.access_counts_;
    this->data_ = other.data_;
    this->size_ = other.size_;
    this->read_counts_ = other.read_counts_;

    other.access_counts_ = tmp.access_counts_;
    other.data_ = tmp.data_;
    other.size_ = tmp.size_;
    other.read_counts_ = tmp.read_counts_;
  }

  const uint2 size() const
  {
    return size_;
  }

  const uint length()
  {
    return size_.x * size_.y;
  }

  void reset_access_counts()
  {
    std::memset(&access_counts_[0], 0, sizeof(uint) * size_.x * size_.y);
    for (auto& el : data_) {
      el.reset_count();
    }
  }

  uint get_write_count(uint index)
  {
    return data_[index].get_write_count();
  }

  uint get_read_count(uint index)
  {
    return access_counts_[index] - data_[index].get_write_count();
  }

private:
  uint2 size_;
  std::vector<Element<T>> data_;
  std::vector<uint> access_counts_;
  std::vector<uint> read_counts_;
};
