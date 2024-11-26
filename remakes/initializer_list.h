#pragma once

#include "../crt_remakes/crt_remakes.h"

namespace std {

    template <class T>
    class initializer_list {
    public:
        using value_type = T;
        using reference = const T&;
        using const_reference = const T&;
        using size_type = size_t;
        using iterator = const T*;
        using const_iterator = const T*;

    private:
        const T* _M_array;
        size_type _M_len;

        // Constructor for internal use
        constexpr initializer_list(const T* array, size_type len) noexcept
            : _M_array(array), _M_len(len) {}


    public:
        // Default constructor for an empty initializer list
        constexpr initializer_list() noexcept : _M_array(nullptr), _M_len(0) {}

        template <typename... Args>
        constexpr initializer_list(Args... args) : _M_array(nullptr), _M_len(sizeof...(args)) {
            static T arr[] = { args... }; // Create a static array with the arguments
            _M_array = arr;               // Assign pointer to the array
        }

        // Number of elements
        constexpr size_type size() const noexcept { return _M_len; }

        // Begin iterator
        constexpr const_iterator begin() const noexcept { return _M_array; }

        // End iterator
        constexpr const_iterator end() const noexcept { return _M_array + _M_len; }

        // Factory function to construct an initializer_list
        static constexpr initializer_list<T> create(const T* array, size_type len) noexcept {
            return initializer_list<T>(array, len);
        }
    };

    // Helper functions for range-based for loops
    template <class T>
    constexpr const T* begin(initializer_list<T> il) noexcept {
        return il.begin();
    }

    template <class T>
    constexpr const T* end(initializer_list<T> il) noexcept {
        return il.end();
    }

} // namespace std
