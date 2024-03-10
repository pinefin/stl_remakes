#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./pair.h"
#include "./vector.h"

namespace std {
template <typename K, typename V> class map {
  typedef std::pair<K, V> pair_type;

  std::vector<pair_type> _data;

public:
  map() : _data() {}
  map(map<K, V> &other) { _data = other.data; };
  map(std::vector<pair_type> &vp) : _data(vp){};
  map(std::initializer_list<pair_type> il) {
    _data.resize(il.size());
    int _idx = 0;
    for (auto &p : il) {
      _data.at(_idx++) = p;
    }
  };

  void insert(const pair_type &p) { _data.push_back(p); }

  size_t size() const { return _data.size(); }

  std::vector<pair_type> data() { return _data; }

  V &at(const K &_key) { return this[_key]; }

  V &operator[](const K &_key) {
    K key = _key;
    for (auto &p : _data) {
      if (p.first == key) {
        return p.second;
      }
    }

    _data.push_back(pair_type(key, V()));
    return _data.back().second;
  }

  pair_type *begin() { return _data.begin(); }
  pair_type *end() { return _data.end(); }
  pair_type *rbegin() { return _data.rbegin(); }
  pair_type *rend() { return _data.rend(); }

  bool empty() { return _data.empty(); }

  void clear() { _data.clear(); }

  size_t max_size() { return _data.max_size(); }

  void erase(const K &key) {
    for (auto it = _data.begin(); it != _data.end(); it++) {
      if (it->first == key) {
        _data.erase(it);
        return;
      }
    }
  }

  void erase(pair_type *it) { _data.erase(it); }

  void erase(pair_type *first, pair_type *last) { _data.erase(first, last); }

  void insert(pair_type *first, pair_type *last) {
    _data.insert(_data.end(), first, last);
  }

  void operator=(const vector<pair_type> &other) { _data = other; }

  void operator=(const map<K, V> &other) { _data = other; }

  void operator=(std::initializer_list<pair_type> il) {
    _data = std::vector<std::pair<K, V>>(il);
  }

  // TODO there's more to implement. i'm too lazy right now and it doesnt suit
  // my current needs
};
} // namespace std
