#pragma once

#include <gostd/cpp/atomic.hpp>
#include <gostd/cpp/cstdint.hpp>
#include <gostd/cpp/cstdlib.hpp>

namespace gostd::cpp {

template <class T>
class shared_ptr {
public:
    constexpr shared_ptr() {}
    shared_ptr(const shared_ptr& other)
        : _ptr{other._ptr}, _info{other._info}
    {
        _increment();
    }

    shared_ptr& operator=(const shared_ptr& other) {
        if (_info == other._info) { return *this; }
        _decrement();
        _ptr = other._ptr;
        _info = other._info;
        _increment();
        return *this;
    }

    ~shared_ptr() {
        _decrement();
    }

    void reset() noexcept {
        _decrement();
        _ptr = nullptr;
    }

    template <class Y>
    void reset(Y* ptr, void(*d)(T*)) {
        reset();
        _ptr = ptr;
        _info = reinterpret_cast<info*>(malloc(sizeof(*_info)));
        _info->refs = 1;
        _info->deleter = d;
    }

    T* get() const noexcept { return _ptr; }

    explicit operator bool() const noexcept { return _ptr; }

private:
    struct info {
        atomic<size_t> refs;
        void (*deleter)(T*);
    };

    T* _ptr = nullptr;
    info* _info = nullptr;

    void _increment() {
        if (_info) {
            ++_info->refs;
        }
    }

    void _decrement() {
        if (_ptr && --_info->refs == 0) {
            _info->deleter(_ptr);
            free(_info);
        }
    }
};

} // namespace gostd::cpp
