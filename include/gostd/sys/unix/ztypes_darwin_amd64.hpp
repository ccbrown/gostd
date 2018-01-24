#pragma once

#include <gostd.hpp>

namespace gostd::sys::unix {

constexpr auto AT_FDCWD            = UntypedConstant(-0x2);
constexpr auto AT_REMOVEDIR        = UntypedConstant(0x80);
constexpr auto AT_SYMLINK_FOLLOW   = UntypedConstant(0x40);
constexpr auto AT_SYMLINK_NOFOLLOW = UntypedConstant(0x20);

} // namespace gostd::sys::unix
