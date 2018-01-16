#pragma once

#include <cx.hpp>

#include <cx/sys/unix/asm_darwin_amd64.hpp>
#include <cx/sys/unix/zerrors_darwin_amd64.hpp>
#include <cx/sys/unix/zsysnum_darwin_amd64.hpp>
#include <cx/sys/unix/ztypes_darwin_amd64.hpp>

extern char** environ;

namespace cx::sys::unix {

static auto RawSyscall6(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3, UintPtr a4, UintPtr a5, UintPtr a6) {
    struct { UintPtr r1, r2; Errno errno; } ret;
    auto [r1, r2, errno] = syscall6(trap, a1, a2, a3, a4, a5, a6);
    ret.r1 = r1;
    ret.r2 = r1;
    ret.errno = errno;
    return ret;
}

static auto RawSyscall(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3) {
    return RawSyscall6(trap, a1, a2, a3, 0, 0, 0);
}

static auto Syscall(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3) {
    return RawSyscall(trap, a1, a2, a3);
}

static auto Syscall6(UintPtr trap, UintPtr a1, UintPtr a2, UintPtr a3, UintPtr a4, UintPtr a5, UintPtr a6) {
    return RawSyscall6(trap, a1, a2, a3, a4, a5, a6);
}

static auto Getenv(String key) {
    struct { String value; bool found = false; } ret;
    for (int i = 0; environ[i]; ++i) {
        auto kv = environ[i];
        for (int j = 0; kv[j]; ++j) {
            if (kv[j] == '=') {
                if (key == String(kv, j)) {
                    ret.value = String(kv+j+1);
                    ret.found = true;
                }
                break;
            }
        }
    }
    return ret;
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

static auto Seek(Int fd, Int64 offset, Int whence) {
    struct { Int64 off; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_LSEEK, fd, offset, whence);
    ret.off = r1;
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Openat(Int dirfd, String path, Int flags, Uint32 mode) {
    struct { Int fd; Error err; } ret;
    auto [r1, r2, errno] = Syscall6(SYS_OPENAT, dirfd, UintPtr(path.NullTerminated().CString()), flags, mode, 0, 0);
    ret.fd = r1;
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Open(String path, Int mode, Uint32 perm) {
    return Openat(AT_FDCWD, path, mode, perm);
}

static Error Unlinkat(Int dirfd, String path, Int flags) {
    auto [r1, r2, errno] = Syscall(SYS_UNLINKAT, dirfd, UintPtr(path.NullTerminated().CString()), flags);
    if (errno != 0) {
        return errno;
    }
    return {};
}

static Error Unlink(String path) {
    return Unlinkat(AT_FDCWD, path, 0);
}

static Error Rmdir(String path) {
    return Unlinkat(AT_FDCWD, path, AT_REMOVEDIR);
}

constexpr Int Stdin = 0;
constexpr Int Stdout = 1;
constexpr Int Stderr = 2;

} // namespace cx::sys::unix
