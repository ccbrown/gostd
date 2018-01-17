#pragma once

#include <gostd/strings.hpp>

namespace gostd::path::filepath {

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

} // namespace gostd::path::filepath
