#pragma once

namespace gostd::cpp {

using uint8_t = unsigned char;
using int16_t = short;
using uint16_t = unsigned short;
using int32_t = int;
using uint32_t = unsigned int;
using int64_t = long long;
using uint64_t = unsigned long long;
using uintptr_t = uint64_t;
using size_t = decltype(sizeof(int));

static_assert(sizeof(int32_t) == 4, "");

constexpr const uint64_t UINT64_MAX = uint64_t(-1);

} // namespace gostd::cpp
