#pragma once

#include <cx.hpp>
#include <cx/io.hpp>
#include <cx/sys/unix.hpp>
#include <cx/errors.hpp>

namespace cx::os {

using FileMode = Uint32;

enum : FileMode {
	ModeDir        = 1ul << 31,
  	ModeAppend     = 1ul << 30,
  	ModeExclusive  = 1ul << 29,
  	ModeTemporary  = 1ul << 28,
  	ModeSymlink    = 1ul << 27,
  	ModeDevice     = 1ul << 26,
  	ModeNamedPipe  = 1ul << 25,
  	ModeSocket     = 1ul << 24,
  	ModeSetuid     = 1ul << 23,
  	ModeSetgid     = 1ul << 22,
  	ModeCharDevice = 1ul << 21,
  	ModeSticky     = 1ul << 20,

  	ModeType = ModeDir | ModeSymlink | ModeNamedPipe | ModeSocket | ModeDevice,

  	ModePerm = 0777
};

enum : Int {
  	O_RDONLY = sys::unix::O_RDONLY,
  	O_WRONLY = sys::unix::O_WRONLY,
  	O_RDWR   = sys::unix::O_RDWR,
  	O_APPEND = sys::unix::O_APPEND,
  	O_CREATE = sys::unix::O_CREAT,
  	O_EXCL   = sys::unix::O_EXCL,
  	O_SYNC   = sys::unix::O_SYNC,
  	O_TRUNC  = sys::unix::O_TRUNC,
};

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
    File(UintPtr fd, String name) : _fd{fd}, _name{name} {}
    ~File() {
        sys::unix::Close(_fd);
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

private:
    const UintPtr _fd;
    const String _name;

    Error _wrapErr(String op, Error err) const {
        if (!err) {
            return err;
        }
        return New<PathError>(op, _name, err);
    }
};

extern Ptr<File> Stdin, Stdout, Stderr;

static auto OpenFile(String name, Int flag, FileMode perm) {
    struct { Ptr<File> file; Error err; } ret;
    auto [fd, err] = sys::unix::Open(name, flag|sys::unix::O_CLOEXEC, 0);
    if (err) {
        ret.err = New<PathError>("open", name, err);
        return ret;
    }
    ret.file = New<File>(fd, name);
    return ret;
}

static auto Open(String name) {
    return OpenFile(name, O_RDONLY, 0);
}

} // namespace cx::os
