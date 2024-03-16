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
typedef long intptr_t;
typedef unsigned long uintptr_t;

// Greatest-width integer types
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
using nullptr_t = decltype(nullptr);

using size_t = unsigned int;

// Constants
const int8_t INT8_MIN = -128;
const int8_t INT8_MAX = 127;
const uint8_t UINT8_MAX = 255;
const int16_t INT16_MIN = -32768;
const int16_t INT16_MAX = 32767;
const uint16_t UINT16_MAX = 65535;
const int32_t INT32_MIN = -2147483648;
const int32_t INT32_MAX = 2147483647;
const uint32_t UINT32_MAX = 4294967295;
const int64_t INT64_MIN = -9223372036854775807LL - 1;
const int64_t INT64_MAX = 9223372036854775807LL;
const uint64_t UINT64_MAX = 18446744073709551615ULL;

} // namespace std
