#pragma once

#include <gostd/allocation.hpp>
#include <gostd/cpp.hpp>

namespace gostd {

using Bool = bool;
using Byte = cpp::uint8_t;
using Rune = cpp::int32_t;
using Uint8 = cpp::uint8_t;
using Uint16 = cpp::uint16_t;
using Int = int;
using Int32 = cpp::int32_t;
using Uint = unsigned int;
using Uint32 = cpp::uint32_t;
using Int64 = cpp::int64_t;
using Uint64 = cpp::uint64_t;
using UintPtr = cpp::uintptr_t;

template <typename F>
using Func = cpp::function<F>;

template <typename T>
void Panic(T v) {
    // TODO: ???
    __builtin_trap();
}

template <typename Destination, typename Source>
Int Copy(Destination dst, Source src) {
    auto count = (dst.Len() < src.Len() ? dst.Len() : src.Len());
    if (count > 0 && &dst[0] > &src[0] && &dst[0] <= &src[count-1]) {
        for (Int i = count - 1; i >= 0; --i) {
            dst[i] = src[i];
        }
    } else {
        for (Int i = 0; i < count; ++i) {
            dst[i] = src[i];
        }
    }
    return count;
}

template <typename T>
class Ptr {
public:
    Ptr() {}

    template <typename... Args>
    static Ptr New(Args... args) {
        return Ptr(nullptr, args...);
    }

    T* operator->() const { return &_data[0]; }

    constexpr operator bool() const { return _data; }

    T& operator *() { return _data[0]; }
    const T& operator *() const { return _data[0]; }

private:
    template <typename... Args>
    Ptr(void*, Args... args) : _data{1, args...} {}

    allocation<T> _data;
};

template <typename T, typename... Args>
Ptr<T> New(Args... args) {
    return Ptr<T>::New(args...);
}

template <typename T>
Int Len(T&& v) { return v.Len(); }

class Defer {
public:
    explicit Defer(Func<void()> f) : _f{cpp::move(f)} {}
    ~Defer() { _f(); }

private:
    Func<void()> _f;
};

} // namespace gostd

#include <gostd/_array.hpp>
#include <gostd/_error.hpp>
#include <gostd/_tuple.hpp>
#include <gostd/_slice.hpp>
#include <gostd/_string.hpp>
#include <gostd/_untyped_constant.hpp>
