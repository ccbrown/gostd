#pragma once

#include <gostd/cpp.hpp>
#include <gostd/_numeric_types.hpp>

namespace gostd {

template <typename T, int L>
class Array {
public:
    template <typename N>
    constexpr T& operator[](N i) { return _elements[Int(i).value()]; }

    T _elements[L];
};

} // namespace gostd
