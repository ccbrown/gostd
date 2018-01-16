#pragma once

#include <cx/cpp.hpp>

namespace cx {

template <typename T>
class allocation {
public:
    constexpr allocation() : _block{nullptr} {}

    template <typename... Args>
    explicit allocation(cpp::uint64_t count, Args... args)
        : _block{reinterpret_cast<block*>(cpp::malloc(sizeof(block)+sizeof(T)*count))}
    {
        for (cpp::uint64_t i = 0; i < count; ++i) {
            new(cpp::placement{_block->data + i}) T(args...);
        }
        _block->refs = 1;
    }

    allocation(const allocation& other) : _block{other._block} {
        _increment();
    }

    allocation& operator=(const allocation& other) {
        if (_block == other._block) { return *this; }
        _decrement();
        _block = other._block;
        _increment();
        return *this;
    }

    ~allocation() {
        _decrement();
    }

    constexpr operator bool() const { return _block; }

    constexpr T& operator[](int i) const { return _block->data[i]; }

    constexpr const cpp::size_t count() const {
        if (!_block) { return 0; }
        return (cpp::malloc_size(_block) - sizeof(block)) / sizeof(T);
    }

private:
    struct block {
        cpp::uint64_t refs;
        T data[0];
    };

    block* _block;

    void _decrement() {
        if (_block && --_block->refs == 0) {
            auto end = count();
            for (cpp::uint64_t i = 0; i < end; ++i) {
                (_block->data + i)->~T();
            }
            cpp::free(_block);
        }
    }

    void _increment() {
        if (_block) {
            ++_block->refs;
        }
    }
};

} // namespace cx
