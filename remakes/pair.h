#pragma once

#include "../crt_remakes/crt_remakes.h"
#include "./initializer_list.h"

namespace std {
template <typename T1, typename T2 = T1> class pair {
public:
  T1 first;
  T2 second;

  pair() : first(), second(){};
  pair(const T1 &_first, const T2 &_second) : first(_first), second(_second){};
  pair(T1 &_first, T2 &_second) : first(_first), second(_second){};
  pair(const pair<T1, T2> &_pair) : first(_pair.first), second(_pair.second){};

  T2 getSecond() { return second; }

  // pair(initializer_list<T1, T2>)
  // pair(pair<T> _p) : first(_p.first), second(_p.second) {};
};
} // namespace std
