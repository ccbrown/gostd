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

} // namespace cx::cpp
