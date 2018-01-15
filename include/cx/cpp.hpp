#pragma once

// consider this file an umbrella include

#include <cx/cpp/any.hpp>
#include <cx/cpp/cstdint.hpp>
#include <cx/cpp/function.hpp>
#include <cx/cpp/reflect.hpp>
#include <cx/cpp/shared_ptr.hpp>
#include <cx/cpp/type_traits.hpp>
#include <cx/cpp/utility.hpp>

namespace cx::cpp {

static size_t strlen(const char* s) {
    size_t len = 0;
    while (s[len]) {
        ++len;
    }
    return len;
}

} // namespace cx::cpp
