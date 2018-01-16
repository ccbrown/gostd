#pragma once

#include <cx/strings.hpp>

namespace cx::path::filepath {

static String Join(String s) {
    return s;
}

template <typename... Args>
static String Join(String a, String b, Args... args) {
    String ab;
    if (strings::HasSuffix(a, "/") || strings::HasPrefix(b, "/")) {
        ab = a + b;
    } else {
        ab = a + "/" + b;
    }
    return Join(ab, args...);
}

} // namespace cx::path::filepath
