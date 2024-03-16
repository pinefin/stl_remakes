#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./cstdint.h"
#include "./unique_ptr.h"

namespace std {

template <typename _SIG> class function;

template <> class function<std::nullptr_t> {
private:
public:
  function(std::nullptr_t) {}

  void operator()(void) const {
    *reinterpret_cast<int *>(0) = 0; // exit
  }
};

template <typename _R, typename... _Args> class function<_R(_Args...)> {
public:
  // Constructor taking a callable object and capturing the surrounding scope
  template <typename F> function(const F &f) : func(new func_holder<F>(f)) {}
  function(std::nullptr_t) : func(nullptr) {}

  _R operator()(_Args... args) const {
    if (func)
      return func->invoke(args...);
    *reinterpret_cast<int *>(0) = 0; // exit
  }

private:
  class func_base {
  public:
    virtual _R invoke(_Args... args) const = 0;
    virtual ~func_base() {}
  };

  template <typename F> class func_holder : public func_base {
  public:
    func_holder(const F &f) : func(f) {}

    _R invoke(_Args... args) const override { return func(args...); }

  private:
    F func;
  };

  func_base *func;
};
} // namespace std
