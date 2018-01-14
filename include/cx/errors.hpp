#pragma once

#include <cx.hpp>

namespace cx::errors {

struct errorString {
    explicit errorString(String s) : s{s} {}

    String Error() const { return s; }

    String s;
};

static Error New(String text) {
    return cx::New<errorString>(text);
}

} // namespace cx::errors
