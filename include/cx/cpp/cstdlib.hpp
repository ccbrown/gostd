#pragma once

#include <cx/cpp/cstdint.hpp>

namespace cx::cpp {

struct placement{ void* ptr; };

} // namespace cx::cpp

void* operator new(cx::cpp::size_t size, cx::cpp::placement placement);
void operator delete(void* ptr, cx::cpp::placement placement);

namespace cx::cpp {

size_t malloc_size(void* ptr);
void* malloc(size_t size);
void free(void* ptr);

} // namespace cx::cpp
