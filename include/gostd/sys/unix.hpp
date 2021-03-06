#pragma once

#include <gostd.hpp>
#include <gostd/unsafe.hpp>

#include <gostd/sys/unix/asm_darwin_amd64.hpp>
#include <gostd/sys/unix/zerrors_darwin_amd64.hpp>
#include <gostd/sys/unix/zsysnum_darwin_amd64.hpp>
#include <gostd/sys/unix/ztypes_darwin_amd64.hpp>

extern char** environ;

namespace gostd::sys::unix {

static auto RawSyscall6(Uintptr trap, Uintptr a1, Uintptr a2, Uintptr a3, Uintptr a4, Uintptr a5, Uintptr a6) {
    struct { Uintptr r1, r2; Errno errno; } ret;
    auto [r1, r2, errno] = syscall6(trap.value(), a1.value(), a2.value(), a3.value(), a4.value(), a5.value(), a6.value());
    ret.r1 = r1;
    ret.r2 = r2;
    ret.errno = errno;
    return ret;
}

static auto RawSyscall(Uintptr trap, Uintptr a1, Uintptr a2, Uintptr a3) {
    return RawSyscall6(trap, a1, a2, a3, 0, 0, 0);
}

static auto Syscall(Uintptr trap, Uintptr a1, Uintptr a2, Uintptr a3) {
    return RawSyscall(trap, a1, a2, a3);
}

static auto Syscall6(Uintptr trap, Uintptr a1, Uintptr a2, Uintptr a3, Uintptr a4, Uintptr a5, Uintptr a6) {
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

static auto Environ() {
    Slice<String> ret;
    for (int i = 0; environ[i]; ++i) {
        ret = Append(ret, environ[i]);
    }
    return ret;
}

static Error Close(Int fd) {
    auto [r1, r2, errno] = Syscall(SYS_CLOSE, Uintptr(fd), 0, 0);
    if (errno != 0) {
        return errno;
    }
    return {};
}

static auto Read(Int fd, Slice<Byte> p) {
    struct { Int n; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_READ, Uintptr(fd), Uintptr(unsafe::Pointer(&p[0])), Uintptr(Len(p)));
    ret.n = Int(r1);
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Write(Int fd, Slice<Byte> p) {
    struct { Int n = 0; Error err; } ret;
    if (Len(p) > 0) {
        auto [r1, r2, errno] = Syscall(SYS_WRITE, Uintptr(fd), Uintptr(unsafe::Pointer(&p[0])), Uintptr(Len(p)));
        ret.n = Int(r1);
        if (errno != 0) {
            ret.err = errno;
        }
    }
    return ret;
}

static auto Seek(Int fd, Int64 offset, Int whence) {
    struct { Int64 off; Error err; } ret;
    auto [r1, r2, errno] = Syscall(SYS_LSEEK, Uintptr(fd), Uintptr(offset), Uintptr(whence));
    ret.off = Int64(r1);
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static Error Mkdirat(Int dirfd, String path, Uint32 mode) {
    auto [r1, r2, errno] = Syscall(SYS_MKDIRAT, Uintptr(dirfd), Uintptr(unsafe::Pointer(path.NullTerminated().CString())), Uintptr(mode));
    if (errno != 0) {
        return errno;
    }
    return {};
}

static auto Mkdir(String path, Uint32 mode) {
    return Mkdirat(AT_FDCWD, path, mode);
}

static auto Openat(Int dirfd, String path, Int flags, Uint32 mode) {
    struct { Int fd; Error err; } ret;
    auto [r1, r2, errno] = Syscall6(SYS_OPENAT, Uintptr(dirfd), Uintptr(unsafe::Pointer(path.NullTerminated().CString())), Uintptr(flags), Uintptr(mode), 0, 0);
    ret.fd = Int(r1);
    if (errno != 0) {
        ret.err = errno;
    }
    return ret;
}

static auto Open(String path, Int mode, Uint32 perm) {
    return Openat(AT_FDCWD, path, mode, perm);
}

static Error Unlinkat(Int dirfd, String path, Int flags) {
    auto [r1, r2, errno] = Syscall(SYS_UNLINKAT, Uintptr(dirfd), Uintptr(unsafe::Pointer(path.NullTerminated().CString())), Uintptr(flags));
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

static Error Exec(String argv0, Slice<String> argv, Slice<String> envv) {
    auto argvz = Make<Slice<String>>(Len(argv));
    auto argvp = Make<Slice<const char*>>(Len(argv) + 1);
    for (int i = 0; i < Len(argv); ++i) {
        argvz[i] = argv[i].NullTerminated();
        argvp[i] = argvz[i].CString();
    }
    argvp[Len(argv).value()] = nullptr;

    auto envvz = Make<Slice<String>>(Len(envv));
    auto envvp = Make<Slice<const char*>>(Len(envv) + 1);
    for (int i = 0; i < Len(envv); ++i) {
        envvz[i] = envv[i].NullTerminated();
        envvp[i] = envvz[i].CString();
    }
    envvp[Len(envv).value()] = nullptr;

    auto [r1, r2, errno] = Syscall(SYS_EXECVE, Uintptr(unsafe::Pointer(argv0.NullTerminated().CString())), Uintptr(unsafe::Pointer(&argvp[0])), Uintptr(unsafe::Pointer(&envvp[0])));
    if (errno != 0) {
        return errno;
    }
    return {};
}

struct Timeval {
    Int64 Sec;
    Int64 Usec;
};

struct Rusage {
    Timeval Utime;
    Timeval Stime;
    Int64 Maxrss;
    Int64 Ixrss;
    Int64 Idrss;
    Int64 Isrss;
    Int64 Minflt;
    Int64 Majflt;
    Int64 Nswap;
    Int64 Inblock;
    Int64 Oublock;
    Int64 Msgsnd;
    Int64 Msgrcv;
    Int64 Nsignals;
    Int64 Nvcsw;
    Int64 Nivcsw;
};

struct WaitStatus {
    Uint32 status;

    constexpr bool Exited() const {
        return (status & 0x7f) == 0x00;
    }

    constexpr bool Signaled() const {
        return (status & 0x7f) != 0x7f && (status & 0x7f) != 0;
    }

    constexpr bool CoreDump() const {
        return Signaled() && (status & 0x80) != 0;
    }

    constexpr Int ExitStatus() const {
        return Exited() ? Int(status >> 8) : -1;
    }
};

static auto Wait4(Int pid, WaitStatus* wstatus, Int options, Rusage* rusage) {
    struct { Int wpid; Error err; } ret;
    auto [r1, r2, errno] = Syscall6(SYS_WAIT4, Uintptr(pid), Uintptr(unsafe::Pointer(&wstatus->status)), Uintptr(options), Uintptr(unsafe::Pointer(rusage)), 0, 0);
    if (errno != 0) {
        ret.err = errno;
        return ret;
    }
    ret.wpid = Int(r1);
    return ret;
}

struct Timespec {
    Int64 Sec;
    Int64 Nsec;
};

struct Stat_t {
    Uint64 Dev;
    Uint64 Ino;
    Uint64 Nlink;
    Uint32 Mode;
    Uint32 Uid;
    Uint32 Gid;
    Int32 X__pad0;
    Uint64 Rdev;
    Int64 Size;
    Int64 Blksize;
    Int64 Blocks;
    Timespec Atim;
    Timespec Mtim;
    Timespec Ctim;
    Int64 X__unused[3];
};

static Error Lstat(String path, Stat_t* stat) {
    auto [r1, r2, errno] = Syscall(SYS_LSTAT, Uintptr(unsafe::Pointer(path.NullTerminated().CString())), Uintptr(unsafe::Pointer(stat)), 0);
    if (errno != 0) {
        return errno;
    }
    return {};
}

static auto Getdirentries(Int fd, Slice<Byte> buf, Uintptr* basep) {
    struct { Int n = 0; Error err; } ret;
    auto [r1, r2, errno] = Syscall6(SYS_GETDIRENTRIES64, Uintptr(fd), Uintptr(unsafe::Pointer(&buf[0])), Uintptr(Len(buf)), Uintptr(unsafe::Pointer(basep)), 0, 0);
    if (errno != 0) {
        ret.err = errno;
    }
    ret.n = Int(r1);
    return ret;
}

static Error Chmod(String path, Uint32 mode) {
    auto [r1, r2, errno] = Syscall(SYS_CHMOD, Uintptr(unsafe::Pointer(path.NullTerminated().CString())), Uintptr(mode), 0);
    if (errno != 0) {
        return errno;
    }
    return {};
}

constexpr auto Stdin = UntypedConstant(0);
constexpr auto Stdout = UntypedConstant(1);
constexpr auto Stderr = UntypedConstant(2);

} // namespace gostd::sys::unix
