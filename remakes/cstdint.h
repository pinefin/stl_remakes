#pragma once

namespace std {

// Exact-width integer types
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

// Minimum-width integer types
typedef int8_t int_least8_t;
typedef uint8_t uint_least8_t;
typedef int16_t int_least16_t;
typedef uint16_t uint_least16_t;
typedef int32_t int_least32_t;
typedef uint32_t uint_least32_t;
typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;

// Fastest minimum-width integer types
typedef int8_t int_fast8_t;
typedef uint8_t uint_fast8_t;
typedef int16_t int_fast16_t;
typedef uint16_t uint_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast32_t;
typedef int64_t int_fast64_t;
typedef uint64_t uint_fast64_t;

// Integer types capable of holding object pointers
#if defined(__LP64__) or defined(_WIN64) or defined(__x86_64__) or             \
    defined(__aarch64__)
typedef int64_t intptr_t;
typedef uint64_t uintptr_t;
#else
typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
#endif

// Greatest-width integer types
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;
using nullptr_t = decltype(nullptr);
using size_t = uintptr_t;

// Constants
constexpr int8_t INT8_MIN = -128;
constexpr int8_t INT8_MAX = 127;
constexpr uint8_t UINT8_MAX = 255;
constexpr int16_t INT16_MIN = -32768;
constexpr int16_t INT16_MAX = 32767;
constexpr uint16_t UINT16_MAX = 65535;
constexpr int32_t INT32_MIN = -2147483648;
constexpr int32_t INT32_MAX = 2147483647;
constexpr uint32_t UINT32_MAX = 4294967295;
constexpr int64_t INT64_MIN = -9223372036854775807LL - 1;
constexpr int64_t INT64_MAX = 9223372036854775807LL;
constexpr uint64_t UINT64_MAX = 18446744073709551615ULL;

} // namespace std
