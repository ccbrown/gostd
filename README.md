# gostd

This is a toy project where I attempt to rewrite and transpile Go packages with C++ (without using the C++ standard library):

```c++
#include <gostd/fmt.hpp>
#include <gostd/os.hpp>

using namespace gostd;

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

## "Packages"

|Package|Status|Notes|
|-|-|-|
|archive/ar|Original|Like archive/tar, but for `ar` archives. Used by `gostd test`.|
|bytes|Partial|Hand-written as needed.|
|cpp|Original|Includes C++-style implementations (mostly from stdlib) as needed.|
|debug/macho|Partial|Hand-written to the extent that `gostd test` requires on macOS.|
|encoding/binary|Partial|Hand-written as needed.|
|errors|Complete|Hand-written.|
|flag|Partial|Hand-written as needed.|
|fmt|Partial|Hand-written as needed.|
|io|Partial|Hand-written as needed.|
|io/ioutil|Partial|Hand-written as needed.|
|os|Partial|Hand-written as needed.|
|os/exec|Partial|Hand-written as needed.|
|path/filepath|Partial|Hand-written as needed.|
|reflect|Partial|Most functionality isn't really even possible in C++.|
|runtime|Partial|Hand-written as needed.|
|sort|Partial|Hand-written as needed.|
|strconv|Partial|Hand-written as needed.|
|strings|Partial|Hand-written as needed.|
|sync/atomic|Partial|Hand-written as needed.|
|sys/unix|Partial|Hand-written as needed.|
|testing|Partial|Hand-written as needed.|
|time|Partial|Hand-written as needed.|
|unicode|Complete|Transpiled.|
|unicode/utf8|Complete|Transpiled, with passing tests.|
|unicode/utf16|Complete|Transpiled, with passing tests.|
|unsafe|Partial|Hand-written as needed.|

The goal is to eventually transpile most of these packages, along with their full test suites. Tests can be run via `./gostd test libgostd.a`.
