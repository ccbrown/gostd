#include <cx/fmt.hpp>
#include <cx/testing.hpp>

namespace cx::fmt {

void TestSprint(testing::T* t) {
    fmt::Println("foo!");
}

void TestFprint(testing::T* t) {
    fmt::Println("bar!");
}

} // namespace cx::fmt
