#pragma once

#include <gostd/fmt.hpp>

namespace gostd::testing {

class T {
public:
    template <typename... Args>
    void Error(Args&&... args) {
        Log(cpp::forward<Args>(args)...);
        Fail();
    }

    template <typename... Args>
    void Errorf(Args&&... args) {
        Logf(cpp::forward<Args>(args)...);
        Fail();
    }

    void Fail() { _failed = true; }

    void FailNow() {
        Fail();
        SkipNow();
    }

    bool Failed() const { return _failed; }

    template <typename... Args>
    void Fatal(Args&&... args) {
        Log(cpp::forward<Args>(args)...);
        FailNow();
    }

    template <typename... Args>
    void Log(Args&&... args) {
        fmt::Println(cpp::forward<Args>(args)...);
    }

    template <typename... Args>
    void Logf(String format, Args&&... args) {
        fmt::Printf(format, cpp::forward<Args>(args)...);
        fmt::Print("\n");
    }

    void SkipNow() {
        Panic("how do i abort this test?");
    }

private:
    bool _failed = false;
};

// TODO
class B {
public:
    Int N;

    void ResetTimer() {}
};

int testMain(int argc, const char* argv[]);

} // namespace gostd::testing
