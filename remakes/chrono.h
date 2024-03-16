#pragma once

#include "./common_type.h"
#include "./ratio.h"
#include "./time.h"

namespace std {
namespace chrono {

template <typename Rep, typename Period = std::ratio<1>> class duration {
public:
  // Type aliases for clarity
  using rep = Rep;       // The type used to represent the number of ticks
  using period = Period; // The tick period

  // Default constructor initializes to zero
  constexpr duration() noexcept : ticks_(0) {}

  // Constructor taking a number of ticks
  explicit constexpr duration(const rep &ticks) noexcept : ticks_(ticks) {}

  // Arithmetic operators for durations
  constexpr duration operator+() const noexcept { return *this; }

  constexpr duration operator-() const noexcept { return duration(-ticks_); }

  constexpr duration &operator++() noexcept {
    ++ticks_;
    return *this;
  }

  constexpr duration operator++(int) noexcept {
    duration temp(*this);
    ++(*this);
    return temp;
  }

  constexpr duration &operator--() noexcept {
    --ticks_;
    return *this;
  }

  constexpr duration operator--(int) noexcept {
    duration temp(*this);
    --(*this);
    return temp;
  }

  constexpr duration &operator+=(const duration &rhs) noexcept {
    ticks_ += rhs.ticks_;
    return *this;
  }

  constexpr duration &operator-=(const duration &rhs) noexcept {
    ticks_ -= rhs.ticks_;
    return *this;
  }

  constexpr duration &operator*=(const rep &rhs) noexcept {
    ticks_ *= rhs;
    return *this;
  }

  constexpr duration &operator/=(const rep &rhs) noexcept {
    ticks_ /= rhs;
    return *this;
  }

  constexpr duration &operator%=(const rep &rhs) noexcept {
    ticks_ %= rhs;
    return *this;
  }

  // Conversion function to get the number of ticks
  constexpr rep count() const noexcept { return ticks_; }

private:
  rep ticks_; // The number of ticks
};

template <typename Clock, typename Duration = typename Clock::duration>
class time_point {
public:
  using clock = Clock;
  using dur = Duration;

  constexpr time_point() noexcept : d_(dur::zero()) {}

  explicit constexpr time_point(const dur &d) noexcept : d_(d) {}

  template <typename Duration2>
  explicit constexpr time_point(const time_point<clock, Duration2> &t) noexcept
      : d_(t.time_since_epoch()) {}

  constexpr time_point &operator+=(const dur &d) noexcept {
    d_ += d;
    return *this;
  }

  constexpr time_point &operator-=(const dur &d) noexcept {
    d_ -= d;
    return *this;
  }

  constexpr const dur &time_since_epoch() const noexcept { return d_; }

private:
  dur d_;
};

class system_clock {
public:
  using duration = std::chrono::duration<long long, std::ratio<1>>;
  using time_point = std::chrono::time_point<system_clock, duration>;

  static time_point now() noexcept {
    return time_point(duration(time(nullptr)));
  }
};

typedef std::chrono::duration<int64_t, std::atto> seconds;
typedef std::chrono::duration<int64_t, std::deci> deciseconds;
typedef std::chrono::duration<int64_t, std::centi> centiseconds;
typedef std::chrono::duration<int64_t, std::milli> milliseconds;
typedef std::chrono::duration<int64_t, std::nano> nanoseconds;
typedef std::chrono::duration<int64_t, std::micro> microseconds;

template <typename ToUnit = seconds, typename Rep = int64_t, typename Period>
ToUnit duration_cast(const std::chrono::duration<Rep, Period> &right) {
  using ratio =
      typename std::ratio_divide<Period, typename ToUnit::period>::type;

  using cm_tp = std::common_type<
      typename std::common_type<typename ToUnit::rep, Rep>::type,
      intmax_t>::type;

  return ToUnit(static_cast<typename ToUnit::rep>(
      static_cast<cm_tp>(right.count()) * static_cast<cm_tp>(ratio::num) /
      static_cast<cm_tp>(ratio::den)));
}
} // namespace chrono
} // namespace std
