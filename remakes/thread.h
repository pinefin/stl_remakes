#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./algorithm.h"
#include "./functional.h"
#include "./unique_lock.h"

#include "./chrono.h"
#include "./cstdint.h"

#include <pthread.h>

namespace std {
class thread {
public:
  class id {
    uint64_t id_;

  public:
    id() : id_(0) {}
    explicit id(uint64_t id) : id_(id) {}

    bool operator==(const id &other) const { return id_ == other.id_; }
    bool operator!=(const id &other) const { return id_ != other.id_; }
  };

  thread()
      : func_(nullptr), thread_(), detached_(false), joined_(false),
        defaultConstructed_(true){};

  explicit thread(std::function<void()> func)
      : func_(func), detached_(false), joined_(false),
        defaultConstructed_(false) {
    if (pthread_create(&thread_, nullptr, threadFunc, this) != 0) {
      *(char *)0 = 0; // crash (this is a bad way to handle errors, but it's
                      // just for testing purposes
    }
  }

  ~thread() {
    if (!defaultConstructed_ && !detached_ && !joined_) {
      pthread_detach(thread_);
    }
  }

  void detach() {
    if (!detached_) {
      pthread_detach(thread_);
      detached_ = true;
    }
  }

  id get_id() { return id(reinterpret_cast<uint64_t>(thread_)); }

  void join() {
    if (this->joinable()) {
      pthread_join(thread_, nullptr);
      joined_ = true;
    }
  }

  bool joinable() { return !joined_ && !defaultConstructed_ && !detached_; }

private:
  std::function<void()> func_;
  pthread_t thread_;
  bool detached_;
  bool joined_;
  bool defaultConstructed_;

  static void *threadFunc(void *arg) {
    thread *self = static_cast<thread *>(arg);
    self->func_();
    return nullptr;
  }
};

namespace this_thread {
inline thread::id get_id() {
  return thread::id(reinterpret_cast<uint64_t>(pthread_self()));
}

inline void yield() noexcept { sched_yield(); }

template <class Rep, class Period>
void sleep_for(const std::chrono::duration<Rep, Period> &duration) {
#ifdef _WIN32
  // Windows implementation
  Sleep(std::chrono::duration_cast<std::chrono::seconds>(duration).count());
#else
  // POSIX implementation
  usleep(
      std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
#endif
}
}; // namespace this_thread
} // namespace std