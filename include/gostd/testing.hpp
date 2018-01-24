#pragma once

#include <gostd/fmt.hpp>

namespace gostd::testing {

class T {
public:
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

    void SkipNow() {
        Panic("how do i abort this test?");
    }

private:
    bool _failed = false;
};

int testMain(int argc, const char* argv[]);

} // namespace gostd::testing
