#pragma once

#include <gostd.hpp>

namespace gostd::unsafe {

class Pointer {
public:
    template <typename T>
    explicit constexpr Pointer(T* ptr) : _value(reinterpret_cast<decltype(_value.value())>(ptr)) {}
    explicit constexpr operator UintPtr() const { return _value; }
private:
    UintPtr _value;
};

} // namespace gostd::unsafe
