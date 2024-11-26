#pragma once

#include "../crt_remakes/crt_remakes.h"

namespace std {
    template <class _Elem>
    class initializer_list {
    public:
        using value_type = _Elem;
        using reference = const _Elem&;
        using const_reference = const _Elem&;
        using size_type = size_t;

        using iterator = const _Elem*;
        using const_iterator = const _Elem*;

        constexpr initializer_list() noexcept : _First(nullptr), _Last(nullptr) {}

        constexpr initializer_list(const _Elem* _First_arg, const _Elem* _Last_arg) noexcept
            : _First(_First_arg), _Last(_Last_arg) {}

        constexpr const _Elem* begin() const noexcept {
            return _First;
        }

        constexpr const _Elem* end() const noexcept {
            return _Last;
        }

        constexpr size_t size() const noexcept {
            return static_cast<size_t>(_Last - _First);
        }

    private:
        const _Elem* _First;
        const _Elem* _Last;
    };

    template <class _Elem>
    constexpr const _Elem* begin(initializer_list<_Elem> _Ilist) noexcept {
        return _Ilist.begin();
    }

    template <class _Elem>
    constexpr const _Elem* end(initializer_list<_Elem> _Ilist) noexcept {
        return _Ilist.end();
    }
} //namespace std
