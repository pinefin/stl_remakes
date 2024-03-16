#pragma once

#include <sys/syscall.h>
#include <unistd.h>

namespace std {
typedef long time_t;

std::time_t time(std::time_t *time) { return syscall(SYS_gettimeofday, time); }
} // namespace std
