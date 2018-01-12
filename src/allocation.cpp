#include <cx.hpp>

#include <cx/sys/unix/asm_darwin_amd64.hpp>
#include <cx/sys/unix/zerrors_darwin_amd64.hpp>
#include <cx/sys/unix/zsysnum_darwin_amd64.hpp>

namespace cx {

using namespace sys;

struct mallocMetadata {
    UInt64 _unused, length;
};

struct mallocChuck {
    mallocMetadata metadata;
    void* memory;
};

void* malloc(UInt64 size) {
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
    auto [r1, r2, errno] = unix::syscall6(unix::SYS_MUNMAP, UIntPtr(metadata), metadata->length, 0, 0, 0, 0);
    if (errno != 0) {
        Panic("unable to free memory");
    }
}

} // namespace cx
