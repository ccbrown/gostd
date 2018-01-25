#pragma once

#include <gostd.hpp>

namespace gostd::sys::unix {

class Errno {
public:
    constexpr Errno() : _errno{0} {}
    explicit constexpr Errno(Uintptr errno) : _errno{errno} {}

    constexpr Errno& operator=(Uintptr errno) {
        _errno = errno;
        return *this;
    }

    constexpr operator Uintptr() const { return _errno; }

    template <typename T> constexpr bool operator==(T v) const { return _errno == Uintptr(v); }
    template <typename T> constexpr bool operator!=(T v) const { return _errno != Uintptr(v); }

    String Error() const;

private:
    Uintptr _errno;
};

} // namespace gostd::sys::unix
