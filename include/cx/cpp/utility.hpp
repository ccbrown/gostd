#pragma once

#include <cx/cpp/type_traits.hpp>

namespace cx::cpp {

template <class T>
auto forward(typename remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
auto forward(typename remove_reference<T>::type&& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
auto move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}

} // namespace cx::cpp
