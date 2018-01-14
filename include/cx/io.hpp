#pragma once

#include <cx.hpp>

namespace cx::io {

extern Error ErrShortBuffer, ErrShortWrite, EOF;

struct Reader {
    Reader() {}

    template <typename T>
    Reader(T r) {
        Read = [=](Slice<Byte> b) {
            auto [n, err] = r->Read(b);
            return ReadResult{n, err};
        };
    }

    struct ReadResult { Int n; Error err; };
    Func<ReadResult(Slice<Byte>)> Read;
};

struct Writer {
    Writer() {}

    template <typename T>
    Writer(T w) {
        Write = [=](Slice<Byte> b) {
            auto [n, err] = w->Write(b);
            return WriteResult{n, err};
        };
    }

    struct WriteResult { Int n; Error err; };
    Func<WriteResult(Slice<Byte>)> Write;
};

static auto ReadAtLeast(Reader r, Slice<Byte> buf, Int min) {
    struct { Int n = 0; Error err; } ret;
    if (buf.Len() < min) {
        ret.err = ErrShortBuffer;
        return ret;
    }
    while (ret.n < min) {
        auto [n, err] = r.Read(buf.Tail(ret.n));
        ret.n += n;
        if (err) {
            ret.err = err;
            break;
        }
    }
    if (ret.n >= min) {
        ret.err = {};
    }
    return ret;
}

static auto Copy(Writer dst, Reader src) {
    struct { Int64 written = 0; Error err; } ret;
    Slice<Byte> buf(32*1024);
    while (true) {
        auto [n, err] = src.Read(buf);
        if (n > 0) {
            auto [nw, err] = dst.Write(buf.Head(n));
            if (nw > 0) {
                ret.written += nw;
            }
            if (err) {
                ret.err = err;
                break;
            }
            if (n != nw) {
                ret.err = ErrShortWrite;
                break;
            }
        }
        if (err) {
            if (err != EOF) {
                ret.err = err;
            }
            break;
        }
    }
    return ret;
}

static auto ReadFull(Reader r, Slice<Byte> buf) {
    return ReadAtLeast(r, buf, buf.Len());
}

struct LimitedReader {
    Reader R;
    Int64 N;

    Reader::ReadResult Read(Slice<Byte> p) {
        if (N <= 0) {
            return {0, EOF};
        }
        if (p.Len() > N) {
            p = p.Head(N);
        }
        auto [n, err] = R.Read(p);
        N -= n;
        return {n, err};
    }
};

static Reader LimitReader(Reader r, Int64 n) {
    auto ret = New<LimitedReader>();
    ret->R = r;
    ret->N = n;
    return ret;
}

static auto CopyN(Writer dst, Reader src, Int64 n) {
    struct { Int64 written = 0; Error err; } ret;
    auto [written, err] = Copy(dst, LimitReader(src, n));
    if (written == n) {
        ret.written = n;
    } else if (written < n && !err) {
        ret.err = EOF;
    }
    return ret;
}

} // namespace cx::io
