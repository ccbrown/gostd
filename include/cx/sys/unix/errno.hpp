#pragma once

#include <cx.hpp>

namespace cx::sys::unix {

class Errno {
public:
    constexpr Errno() : _errno{0} {}
    explicit constexpr Errno(UintPtr errno) : _errno{errno} {}

    constexpr Errno& operator=(UintPtr errno) {
        _errno = errno;
        return *this;
    }

    constexpr operator UintPtr() const { return _errno; }

    String Error() const;

private:
    UintPtr _errno;
};

} // namespace cx::sys::unix