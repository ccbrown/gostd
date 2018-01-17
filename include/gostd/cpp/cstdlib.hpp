#pragma once

#include <gostd/cpp/cstdint.hpp>

namespace gostd::cpp {

struct placement{ void* ptr; };

} // namespace gostd::cpp

void* operator new(gostd::cpp::size_t size, gostd::cpp::placement placement);
void operator delete(void* ptr, gostd::cpp::placement placement);

namespace gostd::cpp {

size_t malloc_size(void* ptr);
void* malloc(size_t size);
void free(void* ptr);

} // namespace gostd::cpp
