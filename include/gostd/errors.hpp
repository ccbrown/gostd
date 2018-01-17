#pragma once

#include <gostd.hpp>

namespace gostd::errors {

struct errorString {
    explicit errorString(String s) : s{s} {}

    String Error() const { return s; }

    String s;
};

static Error New(String text) {
    return gostd::New<errorString>(text);
}

} // namespace gostd::errors
