#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./cstdint.h"

// #include <type_traits>

namespace std {

template <typename... Ts> struct make_void {
  typedef void type;
};

template <typename... Ts> using void_t = typename make_void<Ts...>::type;

template <typename T> struct remove_reference {
  using type = T;
};

template <typename T> struct remove_reference<T &> {
  using type = T;
};

template <typename T> struct remove_reference<T &&> {
  using type = T;
};

struct true_type {
  static constexpr bool value = true;
  using type = bool;
};

struct false_type {
  static constexpr bool value = false;
  using type = bool;
};

template <typename T> struct remove_cv {
  using type = T;
};

template <typename T> struct remove_cv<const T> {
  using type = T;
};

template <typename T> struct remove_cv<volatile T> {
  using type = T;
};

template <typename T> struct remove_cv<const volatile T> {
  using type = T;
};

template <typename T> struct is_array_impl : std::false_type {};

template <typename T> struct is_array_impl<T[]> : std::true_type {};

template <typename T, std::size_t N>
struct is_array_impl<T[N]> : std::true_type {};

template <typename T>
struct is_array : is_array_impl<typename std::remove_cv<T>::type> {};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <bool B, typename T, typename F> struct conditional {
  using type = T;
};

template <typename T> struct add_pointer {
  using type = T *;
};

template <typename> struct is_function : std::false_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...)> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) &> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const &> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile &> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile &> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) &&> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const &&> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile &&> : std::true_type {};

template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile &&> : std::true_type {};

template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
};

template <typename T> struct remove_extent {
  using type = T;
};

template <typename T> struct remove_extent<T[]> {
  using type = T;
};

template <typename T, std::size_t N> struct remove_extent<T[N]> {
  using type = T;
};

template <typename T> struct decay {
private:
  using U = typename std::remove_reference<T>::type;

public:
  using type = typename std::conditional<
      std::is_array<U>::value, typename std::remove_extent<U>::type *,
      typename std::conditional<std::is_function<U>::value,
                                typename std::add_pointer<U>::type,
                                typename std::remove_cv<U>::type>::type>::type;
};

template <typename T> using decay_t = typename decay<T>::type;

template <typename T1, typename T2> struct _Decayed_cond_oper {
  using type =
      typename std::conditional<(sizeof(T1) > sizeof(T2)), T1, T2>::type;
};

template <class... _Ty> struct common_type;

template <class... _Ty>
using common_type_t = typename common_type<_Ty...>::type;

template <> struct common_type<> {};

template <class _Ty1> struct common_type<_Ty1> : common_type<_Ty1, _Ty1> {};

template <class _Ty1, class _Ty2, class _Decayed1 = decay_t<_Ty1>,
          class _Decayed2 = decay_t<_Ty2>>
struct _Common_type2 : common_type<_Decayed1, _Decayed2> {};

template <class _Ty1, class _Ty2>
struct _Common_type2<_Ty1, _Ty2, _Ty1, _Ty2> : _Decayed_cond_oper<_Ty1, _Ty2> {
};

template <class _Ty1, class _Ty2>
struct common_type<_Ty1, _Ty2> : _Common_type2<_Ty1, _Ty2> {};

template <class _Void, class _Ty1, class _Ty2, class... _Rest>
struct _Common_type3 {};

template <class _Ty1, class _Ty2, class... _Rest>
struct _Common_type3<void_t<common_type_t<_Ty1, _Ty2>>, _Ty1, _Ty2, _Rest...>
    : common_type<common_type_t<_Ty1, _Ty2>, _Rest...> {};

template <class _Ty1, class _Ty2, class... _Rest>
struct common_type<_Ty1, _Ty2, _Rest...>
    : _Common_type3<void, _Ty1, _Ty2, _Rest...> {};
} // namespace std
