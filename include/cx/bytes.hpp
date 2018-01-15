#pragma once

#include <cx.hpp>

namespace cx::bytes {

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

private:
    Slice<Byte> _b;
    Int _offset = 0;
};

} // namespace cx::bytes
