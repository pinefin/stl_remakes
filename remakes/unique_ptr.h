#pragma once

#include "./cstdint.h"

namespace std {
template <typename T> class unique_ptr {
private:
  T *ptr;

public:
  // Constructor
  explicit unique_ptr(T *p = nullptr) : ptr(p) {}

  // Destructor
  ~unique_ptr() { delete ptr; }

  // Move constructor
  unique_ptr(unique_ptr &&other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
  }

  // Move assignment operator
  unique_ptr &operator=(unique_ptr &&other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  // Dereference operator
  T &operator*() const { return *ptr; }

  // Arrow operator
  T *operator->() const { return ptr; }

  // Get the raw pointer
  T *get() const { return ptr; }

  // Reset the pointer
  void reset(T *p = nullptr) {
    if (ptr != p) {
      delete ptr;
      ptr = p;
    }
  }

  // Release the ownership
  T *release() {
    T *temp = ptr;
    ptr = nullptr;
    return temp;
  }

  // Conversion operator
  explicit operator bool() const { return ptr != nullptr; }
};
} // namespace std
