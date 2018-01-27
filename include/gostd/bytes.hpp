#pragma once

#include <gostd.hpp>
#include <gostd/errors.hpp>
#include <gostd/io.hpp>
#include <gostd/unicode/utf8.hpp>

namespace gostd::bytes {

static bool Equal(Slice<Byte> a, Slice<Byte> b) {
    if (Len(a) != Len(b)) {
        return false;
    }
    for (Int i = 0; i < Len(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

static Int IndexByte(Slice<Byte> s, Byte b) {
    for (Int i = 0; i < Len(s); i++) {
        if (s[i] == b) {
            return i;
        }
    }
    return -1;
}

static Int IndexRune(Slice<Byte> s, Rune r) {
    if (r >= 0 && r < unicode::utf8::RuneSelf) {
        return IndexByte(s, Byte(r));
    }
    Panic("not yet implemented");
    return -1;
}

static Func<bool(Rune)> makeCutsetFunc(String cutset) {
    Slice<Byte> b(cutset);
    return [=](Rune r) {
        return IndexRune(b, r) >= 0;
    };
}

static Slice<Byte> TrimRightFunc(Slice<Byte> s, Func<bool(Rune)> f) {
    // TODO: utf8
    while (Len(s) > 0 && f(Rune(s[Len(s) - 1]))) {
        s = s.Head(Len(s)-1);
    }
    return s;
}

static Slice<Byte> TrimRight(Slice<Byte> s, String cutset) {
    return TrimRightFunc(s, makeCutsetFunc(cutset));
}

constexpr Int MinRead = 512;

class Buffer {
public:
    explicit Buffer(Slice<Byte> buf) : _buf{buf} {}

    void Reset() {
        _buf = _buf.Head(0);
        _offset = 0;
    }

    auto Bytes() { return _buf.Tail(_offset); }

    io::Reader::ReadResult ReadFrom(io::Reader r) {
        io::Reader::ReadResult ret;

        if (_offset >= Len(_buf)) {
            Reset();
        }

        while (true) {
            if (auto free = Cap(_buf) - Len(_buf); free < MinRead) {
                auto newBuf = _buf;
                if (_offset+free < MinRead) {
                    newBuf = Make<Slice<Byte>>(Len(_buf) - _offset, 2 * Cap(_buf) + MinRead);
                }
                Copy(newBuf, _buf.Tail(_offset));
                _buf = newBuf.Head(Len(_buf)-_offset);
                _offset = 0;
            }
            auto dest = _buf.Head(Cap(_buf)).Tail(Len(_buf));
            auto [n, err] = r.Read(dest);
            _buf = _buf.Head(Len(_buf) + n);
            ret.n += n;
            if (err) {
                if (err != io::EOF) {
                    ret.err = err;
                }
                break;
            }
        }

        return ret;
    }

private:
    Slice<Byte> _buf;
    Int _offset = 0;
};

class Reader {
public:
    explicit Reader(Slice<Byte> b) : _b{b} {}

    auto Read(Slice<Byte> b) {
        struct { Int n; Error err; } ret;
        if (_offset >= Int64(Len(_b))) {
            ret.err = io::EOF;
        } else {
            ret.n = Int(Copy(b, _b.Tail(_offset)));
            _offset += Int64(ret.n);
        }
        return ret;
    }

    auto ReadAt(Slice<Byte> b, Int64 off) {
        struct { Int n; Error err; } ret;
        if (off < 0) {
            ret.err = errors::New("bytes::Reader::ReaderAt: negative offset");
        } else if (off >= Int64(Len(_b))) {
            ret.err = io::EOF;
        } else {
            ret.n = Copy(b, _b.Tail(off));
            if (ret.n < Len(b)) {
                ret.err = io::EOF;
            }
        }
        return ret;
    }

private:
    Slice<Byte> _b;
    Int64 _offset = 0;
};

} // namespace gostd::bytes
