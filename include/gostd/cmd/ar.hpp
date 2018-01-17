#pragma once

#include <gostd/fmt.hpp>
#include <gostd/io.hpp>
#include <gostd/os.hpp>
#include <gostd/archive/ar.hpp>

namespace gostd::cmd::ar {

static void showUsage() {
    fmt::Fprintln(os::Stderr, "Usage: ar op file.a [name...]");
}

static int listFiles(String path) {
    auto [f, err] = os::Open(path);
    if (err) {
        fmt::Fprintln(os::Stderr, err);
        return 1;
    }
    archive::ar::Reader archive(f);
    while (true) {
        auto [fi, err] = archive.Next();
        if (err) {
            if (err == io::EOF) {
                return 0;
            }
            fmt::Fprintln(os::Stderr, err);
            return 1;
        }
        fmt::Println(fi->Name);
    }
    return 1;
}

static int Run(Slice<String> args) {
    if (args.Len() >= 2) {
        if (args[0] == "t") {
            return listFiles(args[1]);
        }
    }
    showUsage();
    return 1;
}

} // namespace gostd::cmd::ar
