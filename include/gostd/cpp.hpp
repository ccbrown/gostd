#pragma once

// consider this file an umbrella include

#include <gostd/cpp/any.hpp>
#include <gostd/cpp/atomic.hpp>
#include <gostd/cpp/cstdint.hpp>
#include <gostd/cpp/function.hpp>
#include <gostd/cpp/reflect.hpp>
#include <gostd/cpp/shared_ptr.hpp>
#include <gostd/cpp/type_traits.hpp>
#include <gostd/cpp/utility.hpp>

namespace gostd::cpp {

static size_t strlen(const char* s) {
    size_t len = 0;
    while (s[len]) {
        ++len;
    }
    return len;
}

} // namespace gostd::cpp
