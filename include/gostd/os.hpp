#pragma once

#include <gostd.hpp>
#include <gostd/io.hpp>
#include <gostd/sys/unix.hpp>
#include <gostd/errors.hpp>

namespace gostd::os {

extern Error ErrExist, ErrNotExist;

struct fileMode {};
using FileMode = Uint32::Type<fileMode>;

constexpr auto ModeDir        = FileMode(1ul << 31);
constexpr auto ModeAppend     = FileMode(1ul << 30);
constexpr auto ModeExclusive  = FileMode(1ul << 29);
constexpr auto ModeTemporary  = FileMode(1ul << 28);
constexpr auto ModeSymlink    = FileMode(1ul << 27);
constexpr auto ModeDevice     = FileMode(1ul << 26);
constexpr auto ModeNamedPipe  = FileMode(1ul << 25);
constexpr auto ModeSocket     = FileMode(1ul << 24);
constexpr auto ModeSetuid     = FileMode(1ul << 23);
constexpr auto ModeSetgid     = FileMode(1ul << 22);
constexpr auto ModeCharDevice = FileMode(1ul << 21);
constexpr auto ModeSticky     = FileMode(1ul << 20);

constexpr auto ModeType = ModeDir | ModeSymlink | ModeNamedPipe | ModeSocket | ModeDevice;
constexpr auto ModePerm = FileMode(0777);

constexpr auto O_RDONLY = sys::unix::O_RDONLY;
constexpr auto O_WRONLY = sys::unix::O_WRONLY;
constexpr auto O_RDWR   = sys::unix::O_RDWR;
constexpr auto O_APPEND = sys::unix::O_APPEND;
constexpr auto O_CREATE = sys::unix::O_CREAT;
constexpr auto O_EXCL   = sys::unix::O_EXCL;
constexpr auto O_SYNC   = sys::unix::O_SYNC;
constexpr auto O_TRUNC  = sys::unix::O_TRUNC;

struct PathError {
    PathError(String op, String path, Error err) : Op{op}, Path{path}, Err{err} {}

    String Op;
    String Path;
    Error Err;

    String Error() const {
        return Op + " " + Path + ": " + String(Err);
    }
};

class File {
public:
    File(UintPtr fd, String name) : _fd{Int(fd)}, _name{name} {}
    ~File() {
        Close();
    }

    Error Close() {
        if (_fd != -1) {
            sys::unix::Close(_fd);
            _fd = -1;
        }
        return {};
    }

    auto Read(Slice<Byte> b) const {
        auto [n, err] = sys::unix::Read(_fd, b);
        err = _wrapErr("read", err);
        struct { Int n; Error err; } ret{n, err};
        if (n == 0 && !err) {
            ret.err = io::EOF;
        }
        return ret;
    }

    auto Seek(Int64 offset, Int whence) const {
        auto ret = sys::unix::Seek(_fd, offset, whence);
        ret.err = _wrapErr("seek", ret.err);
        return ret;
    }

    auto ReadAt(Slice<Byte> b, Int64 off) const {
        struct { Int n = 0; Error err; } ret;
        if (off < 0) {
            ret.err = New<PathError>("readat", _name, errors::New("negative offset"));
            return ret;
        }

        if (auto [_, err] = Seek(off, io::SeekStart); err) {
            ret.err = _wrapErr("read", err);
            return ret;
        }

        auto [n, err] =  Read(b);
        ret.n = n;
        ret.err = err;
        return ret;
    }

    auto Write(Slice<Byte> b) const {
        auto [n, err] = sys::unix::Write(_fd, b);
        err = _wrapErr("write", err);
        struct { Int n; Error err; } ret{n, err};
        return ret;
    }

    auto Name() const { return _name; }

private:
    Int _fd;
    const String _name;

    Error _wrapErr(String op, Error err) const {
        if (!err) {
            return err;
        }
        return New<PathError>(op, _name, err);
    }
};

extern Ptr<File> Stdin, Stdout, Stderr;

static Uint32 syscallMode(FileMode i) {
    auto o = Uint32(i & ModePerm);
    if (i & ModeSetuid) {
        o |= sys::unix::S_ISUID;
    }
    if (i & ModeSetgid) {
        o |= sys::unix::S_ISGID;
    }
    if (i & ModeSticky) {
        o |= sys::unix::S_ISVTX;
    }
    return o;
}

static auto OpenFile(String name, Int flag, FileMode perm) {
    struct { Ptr<File> file; Error err; } ret;
    auto [fd, err] = sys::unix::Open(name, flag|sys::unix::O_CLOEXEC, syscallMode(perm));
    if (err) {
        ret.err = New<PathError>("open", name, err);
        return ret;
    }
    ret.file = New<File>(UintPtr(fd), name);
    return ret;
}

static auto Open(String name) {
    return OpenFile(name, O_RDONLY, 0);
}

static auto Getenv(String key) {
    return sys::unix::Getenv(key);
}

static auto Environ() {
    return sys::unix::Environ();
}

static String TempDir() {
    if (auto [v, ok] = Getenv("TMPDIR"); ok) {
        return v;
    }
    return "/tmp";
}

static Error Remove(String name) {
    if (auto e = sys::unix::Unlink(name); !e) {
        return {};
    } else if (auto e1 = sys::unix::Rmdir(name); !e1) {
        return {};
    } else {
        return New<PathError>("remove", name, e1 == sys::unix::ENOTDIR ? e : e1);
    }
}

static Error underlyingError(Error err) {
    if (auto [pe, ok] = err.As<Ptr<PathError>>(); ok) {
        return pe->Err;
    }
    // TODO: add LinkError and SyscallError
    return err;
}

static bool IsExist(Error err) {
    err = underlyingError(err);
    return err == sys::unix::EEXIST || err == sys::unix::ENOTEMPTY || err == ErrExist;
}

static bool IsNotExist(Error err) {
    err = underlyingError(err);
    return err == sys::unix::ENOENT || err == ErrNotExist;
}

struct ProcAttr {
    Slice<String> Env;
};

class ProcessState {
public:
    ProcessState(Int pid, sys::unix::WaitStatus status, Ptr<sys::unix::Rusage> rusage)
        : _pid{pid}, _status{status}, _rusage{rusage} {}

    constexpr bool Success() const {
        return _status.ExitStatus() == 0;
    }

    explicit operator String() const {
        String ret;
        if (_status.Exited()) {
            ret = "exit status " + itoa(_status.ExitStatus());
        } else {
            // TODO
            ret = "signaled, stopped, or continued";
        }
        if (_status.CoreDump()) {
            ret = ret + " (core dumped)";
        }
        return ret;
    }

private:
    Int _pid;
    sys::unix::WaitStatus _status;
    Ptr<sys::unix::Rusage> _rusage;
};

struct Process {
    Int Pid = -1;

    auto Wait() {
        struct { Ptr<ProcessState> ps; Error err; } ret;
        if (Pid == -1) {
            ret.err = sys::unix::EINVAL;
            return ret;
        }

        sys::unix::WaitStatus status;
        auto rusage = New<sys::unix::Rusage>();
        auto [pid, err] = sys::unix::Wait4(Pid, &status, 0, &*rusage);
        if (err) {
            ret.err = err;
            return ret;
        }
        ret.ps = New<ProcessState>(pid, status, rusage);
        return ret;
    }
};

static auto StartProcess(String argv0, Slice<String> argv, ProcAttr* attr) {
    struct { Ptr<Process> p; Error err; } ret;

    if (auto [r1, r2, errno] = sys::unix::RawSyscall(sys::unix::SYS_FORK, 0, 0, 0); errno != 0) {
        ret.err = errno;
        return ret;
    } else if (r2 == 0) {
        ret.p = New<Process>();
        ret.p->Pid = Int(r1);
        return ret;
    }

    // TODO: lots of stuff to add here

    sys::unix::Exec(argv0, argv, attr->Env);

    while (true) {
        sys::unix::RawSyscall(sys::unix::SYS_EXIT, 253, 0, 0);
    }
}

static auto Create(String name) {
    return OpenFile(name, O_RDWR|O_CREATE|O_TRUNC, 0666);
}

static auto Chmod(String name, FileMode mode) {
    return sys::unix::Chmod(name, syscallMode(mode));
}

static Error Mkdir(String name, FileMode perm) {
    if (auto err = sys::unix::Mkdir(name, syscallMode(perm)); err) {
        return New<PathError>("mkdir", name, err);
    }
    return {};
}

struct FileInfo {
    constexpr bool IsDir() const { return (mode & ModeDir) != 0; }

    FileMode mode;
};

static auto Lstat(String name) {
    struct { FileInfo fi; Error err; } ret;
    sys::unix::Stat_t stat;
    if (auto err = sys::unix::Lstat(name, &stat); err) {
        ret.err = New<PathError>("lstat", name, err);
        return ret;
    }

    ret.fi.mode = FileMode(stat.Mode & 0777);
    return ret;
}

} // namespace gostd::os
