# cx

This is a toy project where I attempt to rewrite Go packages in C++ from scratch (without using the C++ standard library):

```c++
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
```

I don't know how useful this is, but I find it fun.
