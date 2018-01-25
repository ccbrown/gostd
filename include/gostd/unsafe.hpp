#pragma once

#include <gostd.hpp>

namespace gostd::unsafe {

class Pointer {
public:
    explicit constexpr Pointer(Uintptr value) : _value{value} {}

    template <typename T>
    explicit constexpr Pointer(T* ptr) : _value(reinterpret_cast<decltype(_value.value())>(ptr)) {}

    explicit constexpr operator Uintptr() const { return _value; }

    constexpr Uintptr& value() { return _value; }
    constexpr const Uintptr& value() const { return _value; }

private:
    Uintptr _value;
};

} // namespace gostd::unsafe
