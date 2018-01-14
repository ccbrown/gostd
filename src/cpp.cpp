#include <cx/cpp.hpp>

#include <cx/sys/unix/asm_darwin_amd64.hpp>
#include <cx/sys/unix/zerrors_darwin_amd64.hpp>
#include <cx/sys/unix/zsysnum_darwin_amd64.hpp>

void* operator new(cx::cpp::size_t size, cx::cpp::placement placement) {
    return placement.ptr;
}

void operator delete(void* ptr, cx::cpp::placement placement) {}

namespace cx::cpp {

using namespace sys;

struct mallocMetadata {
    size_t length;
};

size_t malloc_size(void* ptr) {
    auto metadata = reinterpret_cast<mallocMetadata*>(ptr) - 1;
    return metadata->length - sizeof(mallocMetadata);
}

void* malloc(size_t size) {
    auto length = size + sizeof(mallocMetadata);
    auto [r1, r2, errno] = unix::syscall6(unix::SYS_MMAP, 0, length, unix::PROT_READ | unix::PROT_WRITE, unix::MAP_PRIVATE | unix::MAP_ANONYMOUS, -1, 0);
    if (errno != 0) {
        Panic("unable to allocate memory");
    }
    auto metadata = reinterpret_cast<mallocMetadata*>(r1);
    metadata->length = length;
    return metadata + 1;
}

void free(void* ptr) {
    auto metadata = reinterpret_cast<mallocMetadata*>(ptr) - 1;
    auto [r1, r2, errno] = unix::syscall6(unix::SYS_MUNMAP, UintPtr(metadata), metadata->length, 0, 0, 0, 0);
    if (errno != 0) {
        Panic("unable to free memory");
    }
}

} // namespace cx::cpp
