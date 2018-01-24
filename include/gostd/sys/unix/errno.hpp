#pragma once

#include <gostd.hpp>

namespace gostd::sys::unix {

class Errno {
public:
    constexpr Errno() : _errno{0} {}
    explicit constexpr Errno(UintPtr errno) : _errno{errno} {}

    constexpr Errno& operator=(UintPtr errno) {
        _errno = errno;
        return *this;
    }

    constexpr operator UintPtr() const { return _errno; }

    template <typename T> constexpr bool operator==(T v) const { return _errno == UintPtr(v); }
    template <typename T> constexpr bool operator!=(T v) const { return _errno != UintPtr(v); }

    String Error() const;

private:
    UintPtr _errno;
};

} // namespace gostd::sys::unix
