#include <gostd/fmt.hpp>
#include <gostd/testing.hpp>

namespace gostd::fmt {

void TestSprint(testing::T* t) {
    auto s = Sprint(-123);
    if (s != "-123") {
        t->Fatal("expected -123, got", s);
    }
}

} // namespace gostd::fmt
