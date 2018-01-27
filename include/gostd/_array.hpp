#pragma once

#include <gostd/cpp.hpp>
#include <gostd/_numeric_types.hpp>
#include <gostd/_slice.hpp>

namespace gostd {

template <typename T, int L>
class Array {
public:
    template <typename... Args>
    explicit Array(Args&&... args) {
        _initialize(0, cpp::forward<Args>(args)...);
    }

    template <typename N>
    constexpr T& operator[](N i) {
        if (Int(i) >= L) {
            Panic("out of bounds");
        }
        return _data[Int(i)];
    }

    constexpr Int len() const { return L; }

    template <typename N>
    Slice<T> Head(N end) const {
        if (Int(end) > L) {
            Panic("out of bounds");
        }
        return Slice<T>(_data, 0, Int(end));
    }

    template <typename N>
    Slice<T> Tail(N start) const {
        if (Int(start) > L) {
            Panic("out of bounds");
        }
        return Slice<T>(_data, Int(start), Int(L));
    }

private:
    allocation<T> _data{Uint64(L)};

    void _initialize(Int i) {}

    template <typename... Rem>
    void _initialize(Int i, T next, Rem&&... rem) {
        _data[i] = cpp::move(next);
        return _initialize(i + 1, cpp::forward<Rem>(rem)...);
    }
};

} // namespace gostd
