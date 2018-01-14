#pragma once

#include <cx.hpp>

namespace cx::errors {

struct errorString {
    String Error() const { return s; }

    String s;
};

static Error New(String text) {
    return errorString{text};
}

} // namespace cx::errors
