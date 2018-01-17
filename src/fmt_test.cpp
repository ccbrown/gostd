#include <gostd/fmt.hpp>
#include <gostd/testing.hpp>

namespace gostd::fmt {

void TestSprint(testing::T* t) {
    fmt::Println("foo!");
}

void TestFprint(testing::T* t) {
    fmt::Println("bar!");
}

} // namespace gostd::fmt
