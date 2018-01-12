#pragma once

#include <cx/allocation.hpp>
#include <cx/typedefs.hpp>

namespace cx {

template <typename T>
void Panic(T v) {
    // TODO: ???
    __builtin_trap();
}

class String {
public:
    constexpr String() : _len{0} {}

    String(const char* s) : _len{0} {
        while (s[_len]) {
            ++_len;
        }
        _data = allocation<Byte>{_len};
        for (auto i = 0; i < _len; ++i) {
            _data[i] = s[i];
        }
    }

    constexpr Byte operator[](int i) const {
        if (i >= _len) {
            Panic("out of bounds");
        }
        return _data[i];
    }

    constexpr UInt64 Len() const { return _len; }

    String operator+(String s) const {
        auto len = Len() + s.Len();
        allocation<Byte> data{len};
        for (auto i = 0; i < Len(); ++i) {
            data[i] = _data[i];
        }
        for (auto i = 0; i < s.Len(); ++i) {
            data[Len() + i] = s[i];
        }
        return String{data, len};
    }

private:
    String(allocation<Byte> data, UInt64 len) : _data{data}, _len{len} {}

    allocation<Byte> _data;
    UInt64 _len;
};

template <typename T>
static String operator+(T prefix, String suffix) {
    return String(prefix) + suffix;
}

template <typename T>
class Slice {
public:
    constexpr Slice() : _len{0}, _cap{0} {}

    explicit Slice(String s) : _data{s.Len()}, _len{s.Len()}, _cap{s.Len()} {
        for (auto i = 0; i < _len; ++i) {
            _data[i] = s[i];
        }
    }

    constexpr T& operator[](int i) {
        if (i >= _len) {
            Panic("out of bounds");
        }
        return _data[i];
    }

    constexpr UInt64 Len() const { return _len; }

private:
    allocation<T> _data;
    const UInt64 _len;
    const UInt64 _cap;
};

class Error {
public:
    constexpr Error() {}

    template <typename T>
    constexpr Error(T err) : _set{err}, _error{err.Error()} {}

    template <typename T>
    constexpr void operator=(T err) {
        _set = err;
        _error = err.Error();
    }

    explicit constexpr operator bool() const { return _set; }
    explicit operator String() const { return _error; }

private:
    bool _set = false;
    String _error;
};

} // namespace cx
