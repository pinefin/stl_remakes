#pragma once

#include "../crt_remakes/crt_remakes.h"

namespace std {
template <typename _M> class unique_lock {
public:
  explicit unique_lock(_M &m) : mutex(m) {
    mutex.lock();
    locked = true;
  }

  ~unique_lock() {
    if (locked) {
      mutex.unlock();
    }
  }

  // Move constructor and move assignment operator
  unique_lock(unique_lock &&other) noexcept
      : mutex(other.mutex), locked(other.locked) {
    other.locked = false;
  }

  unique_lock &operator=(unique_lock &&other) noexcept {
    if (this != &other) {
      if (locked) {
        mutex.unlock();
      }
      mutex = other.mutex;
      locked = other.locked;
      other.locked = false;
    }
    return *this;
  }

  // Deleted copy constructor and copy assignment operator
  unique_lock(const unique_lock &) = delete;
  unique_lock &operator=(const unique_lock &) = delete;

private:
  _M &mutex;
  bool locked;
};
} // namespace std
