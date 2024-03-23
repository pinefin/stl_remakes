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
#ifdef UNIX
        pthread_mutex_t m_mutex;
#else
        CRITICAL_SECTION m_mutex;
#endif

    public:
        // just initialize to defaults
        mutex() {
#ifdef UNIX
            pthread_mutex_init(&m_mutex, NULL);
#else
            InitializeCriticalSection(&m_mutex);
#endif
        }
        virtual ~mutex() {
#ifdef UNIX
            pthread_mutex_unlock(&m_mutex);
            pthread_mutex_destroy(&m_mutex);
#else
            DeleteCriticalSection(&m_mutex);
#endif
        }

        int lock() {
#ifdef UNIX
            return pthread_mutex_lock(&m_mutex);
#else
            EnterCriticalSection(&m_mutex);
            return 0; // Assuming success
#endif
        }
        int trylock() {
#ifdef UNIX
            return pthread_mutex_trylock(&m_mutex);
#else
            return TryEnterCriticalSection(&m_mutex) ? 0 : 1; // Return 0 for success, 1 for failure
#endif
        }
        int unlock() {
#ifdef UNIX
            return pthread_mutex_unlock(&m_mutex);
#else
            LeaveCriticalSection(&m_mutex);
            return 0; // Assuming success
#endif
        }
    };
} // namespace std
