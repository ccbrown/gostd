#pragma once

#include <cx/typedefs.hpp>

namespace cx::sys::unix {

static auto syscall6(UIntPtr trap, UIntPtr a1, UIntPtr a2, UIntPtr a3, UIntPtr a4, UIntPtr a5, UIntPtr a6) {
    struct {
        unsigned long long r1, r2, errno;
    } ret;
    asm(
        "movq %3, %%rax;"
        "movq %4, %%rdi;"
        "movq %5, %%rsi;"
        "movq %6, %%rdx;"
        "movq %7, %%r10;"
        "movq %8, %%r8;"
        "movq %9, %%r9;"
        "syscall;"
        "jc err%=;"
        "movq %%rax, %0;"
        "movq %%rdx, %1;"
        "movq $0, %2;"
        "jmp done%=;"
        "err%=:"
        "movq $-1, %0;"
        "movq $0, %1;"
        "movq %%rax, %2;"
        "done%=:"
        : "=m" (ret.r1), "=m" (ret.r2), "=m" (ret.errno)
        : "r" (0x2000000|trap), "m" (a1), "m" (a2), "m" (a3), "m" (a4), "m" (a5), "m" (a6)
        : "rax", "rdi", "rsi", "rdx", "r8", "r9", "r10", "rcx", "r11", "cc"
    );
    return ret;
}

} // namespace cx::sys::unix
