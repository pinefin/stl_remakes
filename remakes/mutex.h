#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./unique_lock.h"

#if defined(_WIN32)
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace std {
    class mutex {
        friend class CondVar;
#if defined(_WIN32)
        CRITICAL_SECTION m_mutex;
#else
        pthread_mutex_t m_mutex;
#endif

    public:
        // just initialize to defaults
        mutex() {
#if defined(_WIN32)
            InitializeCriticalSection(&m_mutex);
#else
            pthread_mutex_init(&m_mutex, NULL);
#endif
        }
        virtual ~mutex() {
#if defined(_WIN32)
            DeleteCriticalSection(&m_mutex);
#else
            pthread_mutex_unlock(&m_mutex);
            pthread_mutex_destroy(&m_mutex);
#endif
        }

        int lock() {
#if defined(_WIN32)
            EnterCriticalSection(&m_mutex);
            return 0; // Assuming success
#else
            return pthread_mutex_lock(&m_mutex);
#endif
        }
        int trylock() {
#if defined(_WIN32)
            return TryEnterCriticalSection(&m_mutex) ? 0 : 1; // Return 0 for success, 1 for failure
#else
            return pthread_mutex_trylock(&m_mutex);
#endif
        }
        int unlock() {
#if defined(_WIN32)
            LeaveCriticalSection(&m_mutex);
            return 0; // Assuming success
#else
            return pthread_mutex_unlock(&m_mutex);
#endif
        }
    };
} // namespace std