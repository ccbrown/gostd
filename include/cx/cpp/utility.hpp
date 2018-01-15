#pragma once

#include <cx/cpp/type_traits.hpp>

namespace cx::cpp {

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type&& t) noexcept {
    return static_cast<T&&>(t);
}

template <typename T>
typename remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

template <typename T> typename add_rvalue_reference<T>::type declval() noexcept;

template <typename T, T... Ints>
struct integer_sequence {
    typedef T value_type;
    static constexpr size_t size() noexcept { return sizeof...(Ints); }
};

template<size_t... Ints> using index_sequence = integer_sequence<size_t, Ints...>;

#if __has_builtin(__make_integer_seq)
template <class T, T N>
using make_integer_sequence = __make_integer_seq<integer_sequence, T, N>;
#endif

template <size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

} // namespace cx::cpp
