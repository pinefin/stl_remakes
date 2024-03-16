#pragma once

#include "../crt_remakes/crt_remakes.h"
#include "./initializer_list.h"

namespace std {
template <typename... Ts> class tuple;

template <typename T, typename... Ts> class tuple<T, Ts...> {
public:
  tuple(T t, Ts... ts) : head(t), tail(ts...) {}

  template <size_t Index> auto &get() {
    if constexpr (Index == 0)
      return head;
    else
      return tail.template get<Index - 1>();
  }

private:
  T head;
  tuple<Ts...> tail;
};

template <> class tuple<> {
public:
  void get() {}
};
} // namespace std
