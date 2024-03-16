#pragma once

#include "./cstdint.h"

namespace std {
template <intmax_t Num, intmax_t Den = 1> struct ratio {
  static constexpr intmax_t num = Num; // numerator
  static constexpr intmax_t den = Den; // denominator
};

template <class R1, class R2> struct ratio_add {
  using type = ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2> struct ratio_subtract {
  using type = ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2> struct ratio_multiply {
  using type = ratio<R1::num * R2::num, R1::den * R2::den>;
};

template <class R1, class R2> struct ratio_divide {
  using type = ratio<R1::num * R2::den, R1::den * R2::num>;
};

typedef std::ratio<1, 1> atto;
typedef std::ratio<1, 10> deci;
typedef std::ratio<1, 100> centi;
typedef std::ratio<1, 1000> milli;
typedef std::ratio<1, 1000000> micro;
typedef std::ratio<1, 1000000000> nano;
typedef std::ratio<1, 1000000000000> pico;
typedef std::ratio<1, 1000000000000000> femto;
} // namespace std
