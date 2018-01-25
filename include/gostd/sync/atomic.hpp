#pragma once

#include <gostd/unsafe.hpp>

namespace gostd::sync::atomic {

template <typename T>
T integralAdd(T* addr, T delta) {
    return __atomic_add_fetch(&addr->value(), delta.value(), __ATOMIC_SEQ_CST);
}

template <typename T>
bool integralCompareAndSwap(T* addr, T old, T new_) {
    return __atomic_compare_exchange_n(&addr->value(), &old.value(), new_.value(), true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

template <typename T>
T integralLoad(T* addr) {
    return __atomic_load_n(&addr->value(), __ATOMIC_SEQ_CST);
}

template <typename T>
void integralStore(T* addr, T val) {
    __atomic_store_n(&addr->value(), val.value(), __ATOMIC_SEQ_CST);
}

template <typename T>
T integralSwap(T* addr, T new_) {
    return __atomic_exchange_n(&addr->value(), new_.value(), __ATOMIC_SEQ_CST);
}

Int32 AddInt32(Int32* addr, Int32 delta) { return integralAdd(addr, delta); }
Int64 AddInt64(Int64* addr, Int64 delta) { return integralAdd(addr, delta); }
Uint32 AddUint32(Uint32* addr, Uint32 delta) { return integralAdd(addr, delta); }
Uint64 AddUint64(Uint64* addr, Uint64 delta) { return integralAdd(addr, delta); }
Uintptr AddUintptr(Uintptr* addr, Uintptr delta) { return integralAdd(addr, delta); }

bool CompareAndSwapInt32(Int32* addr, Int32 old, Int32 new_) { return integralCompareAndSwap(addr, old, new_); }
bool CompareAndSwapInt64(Int64* addr, Int64 old, Int64 new_) { return integralCompareAndSwap(addr, old, new_); }
bool CompareAndSwapUint32(Uint32* addr, Uint32 old, Uint32 new_) { return integralCompareAndSwap(addr, old, new_); }
bool CompareAndSwapUint64(Uint64* addr, Uint64 old, Uint64 new_) { return integralCompareAndSwap(addr, old, new_); }
bool CompareAndSwapUintptr(Uintptr* addr, Uintptr old, Uintptr new_) { return integralCompareAndSwap(addr, old, new_); }
bool CompareAndSwapPointer(unsafe::Pointer* addr, unsafe::Pointer old, unsafe::Pointer new_) {
    return CompareAndSwapUintptr(&addr->value(), Uintptr(old), Uintptr(new_));
}

Int32 LoadInt32(Int32* addr) { return integralLoad(addr); }
Int64 LoadInt64(Int64* addr) { return integralLoad(addr); }
Uint32 LoadUint32(Uint32* addr) { return integralLoad(addr); }
Uint64 LoadUint64(Uint64* addr) { return integralLoad(addr); }
Uintptr LoadUintptr(Uintptr* addr) { return integralLoad(addr); }
unsafe::Pointer LoadPointer(unsafe::Pointer* addr) {
    return unsafe::Pointer(LoadUintptr(&addr->value()));
}

void StoreInt32(Int32* addr, Int32 val) { return integralStore(addr, val); }
void StoreInt64(Int64* addr, Int64 val) { return integralStore(addr, val); }
void StoreUint32(Uint32* addr, Uint32 val) { return integralStore(addr, val); }
void StoreUint64(Uint64* addr, Uint64 val) { return integralStore(addr, val); }
void StoreUintptr(Uintptr* addr, Uintptr val) { return integralStore(addr, val); }
void StorePointer(unsafe::Pointer* addr, unsafe::Pointer val) {
    return StoreUintptr(&addr->value(), Uintptr(val));
}

Int32 SwapInt32(Int32* addr, Int32 new_) { return integralSwap(addr, new_); }
Int64 SwapInt64(Int64* addr, Int64 new_) { return integralSwap(addr, new_); }
Uint32 SwapUint32(Uint32* addr, Uint32 new_) { return integralSwap(addr, new_); }
Uint64 SwapUint64(Uint64* addr, Uint64 new_) { return integralSwap(addr, new_); }
Uintptr SwapUintptr(Uintptr* addr, Uintptr new_) { return integralSwap(addr, new_); }
unsafe::Pointer SwapPointer(unsafe::Pointer* addr, unsafe::Pointer new_) {
    return unsafe::Pointer(SwapUintptr(&addr->value(), Uintptr(new_)));
}

} // namespace gostd::sync::atomic
