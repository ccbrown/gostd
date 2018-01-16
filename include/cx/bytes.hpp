#pragma once

#include <cx.hpp>
#include <cx/io.hpp>
#include <cx/unicode/utf8.hpp>

namespace cx::bytes {

static Int IndexByte(Slice<Byte> s, Byte b) {
    for (Int i = 0; i < s.Len(); i++) {
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
    while (s.Len() > 0 && f(s[s.Len() - 1])) {
        s = s.Head(s.Len()-1);
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

        if (_offset >= _buf.Len()) {
            Reset();
        }

        while (true) {
            if (auto free = _buf.Cap() - _buf.Len(); free < MinRead) {
                auto newBuf = _buf;
                if (_offset+free < MinRead) {
                    newBuf = Slice<Byte>(_buf.Len() - _offset, 2 * _buf.Cap() + MinRead);
                }
                Copy(newBuf, _buf.Tail(_offset));
                _buf = newBuf.Head(_buf.Len()-_offset);
                _offset = 0;
            }
            auto dest = _buf.Head(_buf.Cap()).Tail(_buf.Len());
            auto [n, err] = r.Read(dest);
            _buf = _buf.Head(_buf.Len() + n);
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
        struct { int n = 0; Error err; } ret;
        if (_offset >= _b.Len()) {
            ret.err = io::EOF;
        } else {
            ret.n = Copy(b, _b.Tail(_offset));
            _offset += ret.n;
        }
        return ret;
    }

    auto ReadAt(Slice<Byte> b, Int64 off) {
        struct { int n = 0; Error err; } ret;
        if (off < 0) {
            ret.err = errors::New("bytes::Reader::ReaderAt: negative offset");
        } else if (off >= _b.Len()) {
            ret.err = io::EOF;
        } else {
            ret.n = Copy(b, _b.Tail(off));
            if (ret.n < b.Len()) {
                ret.err = io::EOF;
            }
        }
        return ret;
    }

private:
    Slice<Byte> _b;
    Int _offset = 0;
};

} // namespace cx::bytes
