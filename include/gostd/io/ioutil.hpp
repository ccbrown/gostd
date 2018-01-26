#pragma once

#include <gostd/bytes.hpp>
#include <gostd/io.hpp>
#include <gostd/os.hpp>
#include <gostd/path/filepath.hpp>
#include <gostd/strconv.hpp>

namespace gostd::io::ioutil {

extern const Writer Discard;

extern Uint32 suffixN;

static String nextSuffix() {
    // TODO: randomize
    suffixN++;
    return strconv::Itoa(Int(suffixN-1));
}

static auto ReadAll(Reader r) {
    struct { Slice<Byte> buf; Error err; } ret;
    auto buf = New<bytes::Buffer>(Make<Slice<Byte>>(0, bytes::MinRead));
    auto [_, err] = buf->ReadFrom(r);
    ret.buf = buf->Bytes();
    ret.err = err;
    return ret;
}

static auto TempDir(String dir = "", String prefix = "") {
    struct { String name; Error err; } ret;

    if (dir == "") {
        dir = os::TempDir();
    }

    for (int i = 0; i < 10000; i++) {
        auto name = path::filepath::Join(dir, prefix+nextSuffix());
        auto err = os::Mkdir(name, 0700);
        if (os::IsExist(err)) {
            continue;
        }
        ret.name = name;
        ret.err = err;
        break;
    }

    return ret;
}

static auto TempFile(String dir = "", String prefix = "") {
    struct { Ptr<os::File> f; Error err; } ret;

    if (dir == "") {
        dir = os::TempDir();
    }

    for (int i = 0; i < 10000; i++) {
        auto name = path::filepath::Join(dir, prefix+nextSuffix());
        auto [f, err] = os::OpenFile(name, os::O_RDWR|os::O_CREATE|os::O_EXCL, 0600);
        if (os::IsExist(err)) {
            continue;
        }
        ret.f = f;
        ret.err = err;
        break;
    }

    return ret;
}

} // namespace gostd::io::ioutil
