#pragma once

#include <cx/typedefs.hpp>

namespace cx {

void* malloc(UInt64 size);
void free(void* ptr);

template <typename T>
class allocation {
public:
    constexpr allocation() : _ptr{nullptr}, _refs{nullptr} {}

    explicit allocation(UInt64 count)
        : _ptr{reinterpret_cast<T*>(malloc(sizeof(T)*count))}
        , _refs{reinterpret_cast<UInt64*>(malloc(sizeof(*_refs)))}
    {
        *_refs = 1;
    }

    allocation(const allocation& other) : _ptr{other._ptr}, _refs{other._refs} {
        ++*_refs;
    }

    allocation& operator=(const allocation& other) {
        if (_refs && --*_refs == 0) {
            free(_ptr);
            free(_refs);
        }
        _ptr = other._ptr;
        _refs = other._refs;
        if (_refs) {
            ++*_refs;
        }
        return *this;
    }

    ~allocation() {
        if (_refs && --*_refs == 0) {
            free(_ptr);
            free(_refs);
        }
    }

    constexpr T& operator[](int i) { return _ptr[i]; }
    constexpr const T& operator[](int i) const { return _ptr[i]; }

private:
    T* _ptr;
    UInt64* _refs;
};

} // namespace cx
