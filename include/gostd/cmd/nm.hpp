#pragma once

#include <gostd/fmt.hpp>
#include <gostd/os.hpp>
#include <gostd/debug/macho.hpp>

namespace gostd::cmd::nm {

static void showUsage() {
    fmt::Fprintln(os::Stderr, "Usage: nm [options] file...");
}

static int listSymbols(String path) {
    auto [f, ferr] = os::Open(path);
    if (ferr) {
        fmt::Fprintln(os::Stderr, ferr);
        return 1;
    }
    auto [macho, err] = debug::macho::NewFile(f);
    if (err) {
        fmt::Fprintln(os::Stderr, err);
        return 1;
    }
    if (macho->Symtab) {
        for (Int i = 0; i < Len(macho->Symtab->Syms); i++) {
            fmt::Println(macho->Symtab->Syms[i].Name);
        }
    }
    return 0;
}

static int Run(Slice<String> args) {
    if (Len(args) >= 1) {
        for (Int i = 0; i < Len(args); i++) {
            if (auto ret = listSymbols(args[i]); ret != 0) {
                return ret;
            }
        }
        return 0;
    }
    showUsage();
    return 1;
}

} // namespace gostd::cmd::nm
