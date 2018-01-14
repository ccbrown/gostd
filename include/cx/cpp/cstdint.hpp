#pragma once

namespace cx::cpp {

using uint8_t = unsigned char;
using int32_t = int;
using int64_t = long long;
using uint64_t = unsigned long long;
using uintptr_t = uint64_t;
using size_t = decltype(sizeof(int));

constexpr const uint64_t UINT64_MAX = uint64_t(-1);

} // namespace cx::cpp
