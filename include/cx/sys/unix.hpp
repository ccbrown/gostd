#pragma once

#include <cx.hpp>

#include <cx/sys/unix/asm_darwin_amd64.hpp>
#include <cx/sys/unix/zerrors_darwin_amd64.hpp>
#include <cx/sys/unix/zsysnum_darwin_amd64.hpp>
#include <cx/sys/unix/ztypes_darwin_amd64.hpp>

namespace cx::sys::unix {

template <typename T>
static String uitoa(T v) {
    char buf[33] = {0};
    auto i = sizeof(buf) - 2;
    while (v >= 10) {
        buf[i] = v%10 + '0';
        --i;
        v /= 10;
    }
    buf[i] = v + '0';
    return buf + i;
}

template <typename T>
static String itoa(T v) {
    if (v < 0) {
        return "-" + uitoa(-v);
    }
    return uitoa(v);
}

class Errno {
public:
    constexpr Errno() : _errno{0} {}
    explicit constexpr Errno(UintPtr errno) : _errno{errno} {}

    constexpr Errno& operator=(UintPtr errno) {
        _errno = errno;
        return *this;
    }

    constexpr operator UintPtr() const { return _errno; }

    String Error() const {
        auto errno = Int(_errno);
        if (errno > 0 && errno <= sizeof(errors) / sizeof(*errors)) {
            return errors[errno];
        }
        return "errno " + itoa(errno);
    }

private:
    UintPtr _errno;
};

static auto RawSyscall(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3) {
    struct { UintPtr r1, r2; Errno errno; } ret;
    auto [r1, r2, errno] = syscall6(trap, a1, a2, a3, 0, 0, 0);
    ret.r1 = r1;
    ret.r2 = r1;
    ret.errno = errno;
    return ret;
}

static auto Syscall(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3) {
    return RawSyscall(trap, a1, a2, a3);
}

static Error Close(Int fd) {
    auto [r1, r2, errno] = Syscall(SYS_CLOSE, fd, 0, 0);
    if (errno != 0) {
        return errno;
    }
    return {};
}

static auto Read(Int fd, Slice<Byte> p) {
    struct { Int n; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_READ, fd, UintPtr(&p[0]), p.Len());
    ret.n = r1;
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Write(Int fd, Slice<Byte> p) {
    struct { Int n = 0; Error err; } ret;
    if (p.Len() > 0) {
        auto [r1, r2, errno] = Syscall(SYS_WRITE, fd, UintPtr(&p[0]), p.Len());
        ret.n = r1;
        if (errno != 0) {
            ret.err = errno;
        }
    }
    return ret;
}

static auto Openat(Int dirfd, String path, Int flags, Uint32 mode) {
    struct { Int fd; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_OPEN, UintPtr(path.NullTerminated().CString()), flags, mode);
    ret.fd = r1;
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Open(String path, Int mode, Uint32 perm) {
    return Openat(AT_FDCWD, path, mode, perm);
}

constexpr Int Stdin = 0;
constexpr Int Stdout = 1;
constexpr Int Stderr = 2;

} // namespace cx::sys::unix
