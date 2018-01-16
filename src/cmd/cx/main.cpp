#include <cx/cmd/ar.hpp>
#include <cx/cmd/nm.hpp>
#include <cx/cmd/test.hpp>
#include <cx/fmt.hpp>
#include <cx/os.hpp>
#include <cx/strconv.hpp>

using namespace cx;

int main(int argc, const char* argv[]) {
    Slice<String> args(argc);
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }

    if (argc > 1 && cx::String(argv[1]) == "ar") {
        return cmd::ar::Run(args.Tail(2));
    } else if (argc > 1 && cx::String(argv[1]) == "nm") {
        return cmd::nm::Run(args.Tail(2));
    } else if (argc > 1 && cx::String(argv[1]) == "test") {
        return cmd::test::Run(args.Tail(2));
    }

    {
        auto [n, err] = fmt::Println("hello, world!");
        if (err) {
            fmt::Fprintln(os::Stderr, "error!", err);
            return 1;
        }
        fmt::Println("wrote", n, "bytes");
    }

    {
        String foo = "foo";
        auto [i, err] = strconv::ParseInt(foo, 0, 32);
        fmt::Println(err);
    }

    return 0;
}
