#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./unique_lock.h"

#ifdef UNIX // Apple has a different pthread implementation
#include <pthread.h>
#else
#include <Windows.h>
#endif

namespace std {
class mutex {
  friend class CondVar;
  pthread_mutex_t m_mutex;

public:
  // just initialize to defaults
  mutex() { pthread_mutex_init(&m_mutex, NULL); }
  virtual ~mutex() {
    pthread_mutex_unlock(&m_mutex);
    pthread_mutex_destroy(&m_mutex);
  }

  int lock() { return pthread_mutex_lock(&m_mutex); }
  int trylock() { return pthread_mutex_trylock(&m_mutex); }
  int unlock() { return pthread_mutex_unlock(&m_mutex); }
};
} // namespace std
