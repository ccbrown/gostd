#pragma once

#include <cx.hpp>

#include <cx/sys/unix/asm_darwin_amd64.hpp>
#include <cx/sys/unix/zerrors_darwin_amd64.hpp>
#include <cx/sys/unix/zsysnum_darwin_amd64.hpp>

namespace cx::sys::unix {

template <typename T>
static String uitoa(T v) {
    char buf[32];
    auto i = sizeof(buf) - 1;
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

struct Errno {
    UIntPtr No;

    constexpr operator bool() const { return No != 0; }

    String Error() const {
        auto errno = Int(No);
        if (errno > 0 && errno <= sizeof(errors) / sizeof(*errors)) {
            return errors[errno];
        }
        return "errno " + itoa(errno);
    }
};

static auto RawSyscall(UIntPtr trap, UIntPtr a1, UIntPtr a2, UIntPtr a3) {
    struct { UIntPtr r1, r2; Errno errno; } ret;
    auto [r1, r2, errno] = syscall6(trap, a1, a2, a3, 0, 0, 0);
    ret.r1 = r1;
    ret.r2 = r1;
    ret.errno.No = errno;
    return ret;
}

static auto Syscall(UIntPtr trap, UIntPtr a1, UIntPtr a2, UIntPtr a3) {
    return RawSyscall(trap, a1, a2, a3);
}

static auto Write(Int fd, Slice<Byte> p) {
    struct { Int n; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_WRITE, 2, UIntPtr(&p[0]), p.Len());
    ret.n = r1;
    ret.err = errno;
    return ret;
}

constexpr Int Stdin = 0;
constexpr Int Stdout = 1;
constexpr Int Stderr = 2;

} // namespace cx::sys::unix
