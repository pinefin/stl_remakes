#pragma once

#include "../crt_remakes/crt_remakes.h"

namespace std {
template <typename T> class optional {
  T data;

public:
  optional() : data() {}
  optional(T data) : data(data) {}
  optional(const optional &other) : data(other.data) {}
  optional(optional &&other) : data(other.data) {}
  optional &operator=(const optional &other) {
    data = other.data;
    return *this;
  }
  optional &operator=(optional &&other) {
    data = other.data;
    return *this;
  }
  ~optional() {}
  T &operator*() { return data; }
  T *operator->() { return &data; }
  operator bool() { return data; }
  bool has_value() { return data; }

  void reset() { data = T(); }

  void swap(optional &other) {
    T temp = data;
    data = other.data;
    other.data = temp;
  }

  void emplace(T data) { this->data = data; }

  T value_or(T default_value) { return data ? data : default_value; }

  T value() { return data; }

  // TODO std::function
  //  optional<T> and_then(std::function<optional<T>(T)> f) {
  //  	return data ? f(data) : optional<T>();
  //  }
};
} // namespace std
