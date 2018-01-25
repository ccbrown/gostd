#pragma once

#include <gostd/cpp/type_traits.hpp>

namespace gostd::cpp {

template <typename T, typename = typename enable_if<is_integral<T>::value>::type>
class atomic {
public:
    atomic() noexcept = default;
    constexpr atomic(T desired) noexcept : _value{desired} {}

    T operator++() volatile noexcept { return fetch_add(1)+1; }
    T operator++(int) volatile noexcept { return fetch_add(1); }
    T operator--() volatile noexcept { return fetch_sub(1)-1; }
    T operator--(int) volatile noexcept { return fetch_sub(1); }

    T fetch_add(T arg) volatile noexcept {
        return __atomic_fetch_add(&_value, arg, __ATOMIC_SEQ_CST);
    }

    T fetch_sub(T arg) volatile noexcept {
        return __atomic_fetch_sub(&_value, arg, __ATOMIC_SEQ_CST);
    }

private:
    T _value;
};

} // namespace gostd::cpp
