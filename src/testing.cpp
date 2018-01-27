#include <gostd/testing.hpp>

#include <gostd/fmt.hpp>

namespace gostd::testing {

struct testDef {
    const char* name;
    void(*rawPtrFunction)(T*);
    void(*ptrFunction)(Ptr<T>);
};

extern testDef tests[];

int testMain(int argc, const char* argv[]) {
    Slice<Ptr<T>> failures;
    for (int i = 0; tests[i].name != nullptr; ++i) {
        auto& test = tests[i];
        fmt::Println("=== RUN  ", test.name);
        auto t = New<T>();
        if (test.rawPtrFunction != nullptr) {
            test.rawPtrFunction(&*t);
        } else {
            test.ptrFunction(t);
        }
        if (t->Failed()) {
            fmt::Println("--- FAIL:", test.name);
            failures = Append(failures, t);
        } else {
            fmt::Println("--- PASS:", test.name);
        }
    }
    if (Len(failures) == 0) {
        fmt::Println("PASS");
    } else {
        fmt::Println("FAIL");
    }
    return Len(failures) > 0 ? 1 : 0;
}

} // namespace gostd::testing
