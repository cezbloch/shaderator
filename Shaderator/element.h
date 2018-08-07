#pragma once

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