#include <cx/cmd/ar.hpp>
#include <cx/fmt.hpp>
#include <cx/os.hpp>

using namespace cx;

int main(int argc, const char* argv[]) {
    Slice<String> args(argc);
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }

    if (argc > 1 && cx::String(argv[1]) == "ar") {
        return cmd::ar::Run(args.Tail(2));
    }

    auto [n, err] = fmt::Println("hello, world!");
    if (err) {
        fmt::Fprintln(os::Stderr, "error!", err);
        return 1;
    }
    fmt::Println("wrote", n, "bytes");
    return 0;
}
