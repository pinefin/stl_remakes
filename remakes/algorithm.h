#pragma once

#include "../crt_remakes/crt_remakes.h"

#include "./pair.h"

namespace std {
template <class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
  while (first != last) {
    if (!pred(*first))
      return false;
    ++first;
  }
  return true;
}

template <class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
  while (first != last) {
    if (pred(*first))
      return true;
    ++first;
  }
  return false;
}

template <class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
  while (first != last) {
    if (pred(*first))
      return false;
    ++first;
  }
  return true;
}

template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function fn) {
  while (first != last) {
    fn(*first);
    ++first;
  }
  return fn; // or, since C++11: return move(fn);
}

template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T &val) {
  while (first != last) {
    if (*first == val)
      return first;
    ++first;
  }
  return last;
}

template <class InputIterator, class UnaryPredicate>
InputIterator find_if(InputIterator first, InputIterator last,
                      UnaryPredicate pred) {
  while (first != last) {
    if (pred(*first))
      return first;
    ++first;
  }
  return last;
}

template <class InputIterator, class UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last,
                          UnaryPredicate pred) {
  while (first != last) {
    if (!pred(*first))
      return first;
    ++first;
  }
  return last;
}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2) {
  if (first2 == last2)
    return last1; // specified in C++11

  ForwardIterator1 ret = last1;

  while (first1 != last1) {
    ForwardIterator1 it1 = first1;
    ForwardIterator2 it2 = first2;
    while (*it1 == *it2) { // or: while (pred(*it1,*it2)) for version (2)
      ++it1;
      ++it2;
      if (it2 == last2) {
        ret = first1;
        break;
      }
      if (it1 == last1)
        return ret;
    }
    ++first1;
  }
  return ret;
}

template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2) {
  while (first1 != last1) {
    for (ForwardIterator it = first2; it != last2; ++it) {
      if (*it == *first1) // or: if (pred(*it,*first)) for version (2)
        return first1;
    }
    ++first1;
  }
  return last1;
}

template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
  if (first != last) {
    ForwardIterator next = first;
    ++next;
    while (next != last) {
      if (*first == *next) // or: if (pred(*first,*next)), for version (2)
        return first;
      ++first;
      ++next;
    }
  }
  return last;
}

template <class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
  while ((first1 != last1) &&
         (*first1 == *first2)) // or: pred(*first1,*first2), for version 2
  {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
  while (first1 != last1) {
    if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2) {
  if (first2 == last2)
    return first1; // specified in C++11

  while (first1 != last1) {
    ForwardIterator1 it1 = first1;
    ForwardIterator2 it2 = first2;
    while (*it1 == *it2) { // or: while (pred(*it1,*it2)) for version 2
      ++it1;
      ++it2;
      if (it2 == last2)
        return first1;
      if (it1 == last1)
        return last1;
    }
    ++first1;
  }
  return last1;
}

template <class InputIterator, class OutputIterator, class UnaryOperator>
OutputIterator transform(InputIterator first1, InputIterator last1,
                         OutputIterator result, UnaryOperator op) {
  while (first1 != last1) {
    *result = op(*first1); // or: *result=binary_op(*first1,*first2++);
    ++result;
    ++first1;
  }
  return result;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
                    OutputIterator result) {
  while (first != last) {
    *result = *first;
    ++result;
    ++first;
  }
  return result;
}
template <class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {
  while (n > 0) {
    *result = *first;
    ++result;
    ++first;
    --n;
  }
  return result;
}
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last,
                       OutputIterator result, UnaryPredicate pred) {
  while (first != last) {
    if (pred(*first)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
                                     BidirectionalIterator1 last,
                                     BidirectionalIterator2 result) {
  while (last != first)
    *(--result) = *(--last);
  return result;
}

template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last,
                    OutputIterator result) {
  while (first != last) {
    *result = std::move(*first);
    ++result;
    ++first;
  }
  return result;
}

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 first,
                                     BidirectionalIterator1 last,
                                     BidirectionalIterator2 result) {
  while (last != first)
    *(--result) = std::move(*(--last));
  return result;
}
template <class T> void swap(T &a, T &b) {
  T c(std::move(a));
  a = std::move(b);
  b = std::move(c);
}
template <class T, size_t N> void swap(T (&a)[N], T (&b)[N]) {
  for (size_t i = 0; i < N; ++i)
    swap(a[i], b[i]);
}
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
                             ForwardIterator2 first2) {
  while (first1 != last1) {
    swap(*first1, *first2);
    ++first1;
    ++first2;
  }
  return first2;
}
template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
  swap(*a, *b);
}
template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T &old_value,
             const T &new_value) {
  while (first != last) {
    if (*first == old_value)
      *first = new_value;
    ++first;
  }
}
template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last,
                            OutputIterator result, const T &old_value,
                            const T &new_value) {
  while (first != last) {
    *result = (*first == old_value) ? new_value : *first;
    ++first;
    ++result;
  }
  return result;
}
template <class ForwardIterator, class UnaryPredicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last,
                UnaryPredicate pred, const T &new_value) {
  while (first != last) {
    if (pred(*first))
      *first = new_value;
    ++first;
  }
}
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T &val) {
  while (first != last) {
    *first = val;
    ++first;
  }
}
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T &val) {
  while (n > 0) {
    *first = val;
    ++first;
    --n;
  }
  return first; // since C++11
}
template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
  while (first != last) {
    *first = gen();
    ++first;
  }
}
template <class OutputIterator, class Size, class Generator>
void generate_n(OutputIterator first, Size n, Generator gen) {
  while (n > 0) {
    *first = gen();
    ++first;
    --n;
  }
}
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last,
                       const T &val) {
  ForwardIterator result = first;
  while (first != last) {
    if (!(*first == val)) {
      if (result != first)
        *result = move(*first);
      ++result;
    }
    ++first;
  }
  return result;
}

template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                          UnaryPredicate pred) {
  ForwardIterator result = first;
  while (first != last) {
    if (!pred(*first)) {
      if (result != first)
        *result = std::move(*first);
      ++result;
    }
    ++first;
  }
  return result;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
                           OutputIterator result, const T &val) {
  while (first != last) {
    if (!(*first == val)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
                              OutputIterator result, UnaryPredicate pred) {
  while (first != last) {
    if (!pred(*first)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}

template <class T> const T &min(const T &a, const T &b) {
  return !(b < a) ? a : b; // or: return !comp(b,a)?a:b; for version (2)
}

template <class T> const T &max(const T &a, const T &b) {
  return (a < b) ? b : a; // or: return comp(a,b)?b:a; for version (2)
}

template <class T> pair<const T &, const T &> minmax(const T &a, const T &b) {
  return (b < a) ? pair<const T &, const T &>(b, a)
                 : pair<const T &, const T &>(a, b);
}

} // namespace std
