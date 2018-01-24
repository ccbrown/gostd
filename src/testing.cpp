#include <gostd/testing.hpp>

#include <gostd/fmt.hpp>

namespace gostd::testing {

extern void(*testFunctions[])(T*);
extern const char* testNames[];

int testMain(int argc, const char* argv[]) {
    for (int i = 0; testNames[i] != nullptr; ++i) {
        fmt::Println("=== RUN  ", testNames[i]);
        testFunctions[i](nullptr);
        fmt::Println("--- PASS:", testNames[i]);
    }
    fmt::Println("PASS");
    return 0;
}

} // namespace gostd::testing
