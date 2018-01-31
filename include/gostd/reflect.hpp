#pragma once

#include <gostd.hpp>

namespace gostd::reflect {

template <typename T>
bool DeepEqual(T& a, T& b);

template <typename T>
struct deepEqual {
    static bool equal(T& a, T& b) {
        return a == b;
    }
};

template <typename T>
struct deepEqual<Slice<T>> {
    static bool equal(Slice<T>& a, Slice<T>& b) {
        if (Len(a) != Len(b)) {
            return false;
        }
        for (Int i = 0; i < Len(a); i++) {
            if (!DeepEqual(a[i], b[i])) {
                return false;
            }
        }
        return true;
    }
};

// TODO: pointers and other types
template <typename T>
bool DeepEqual(T& a, T& b) {
    return deepEqual<T>::equal(a, b);
}

} // namespace gostd::reflect
