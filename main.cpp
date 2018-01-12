#include <cx/fmt.hpp>
#include <cx/os.hpp>

using namespace cx;

int main() {
    auto [n, err] = fmt::Println("hello, world!");
    if (err) {
        fmt::Fprintln(os::Stderr, "error!", err);
        return 1;
    }
    fmt::Println("wrote", n, "bytes");
    return 0;
}
