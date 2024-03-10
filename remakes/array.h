#pragma once

#include <crt_remakes.h>

#include "initializer_list.h"

namespace std {
template <typename T, size_t size> class array {
private:
  T *_data;

public:
  array() { _data = new T[size]; }
  array(std::initializer_list<T> il) {
    _data = new T[size];
    size_t i = 0;
    for (auto &elem : il) {
      _data[i] = elem;
      i++;
    }
  }
  ~array() { delete[] _data; }

  T &operator[](size_t index) { return _data[index]; }
  const T &operator[](size_t index) const { return _data[index]; }

  T *begin() { return _data; }
  T *end() { return _data + size; }

  const T *begin() const { return _data; }
  const T *end() const { return _data + size; }

  size_t length() const { return size; };

  T *data() { return _data; }
};
} // namespace std
