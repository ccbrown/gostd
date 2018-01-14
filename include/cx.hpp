#pragma once

#include <cx/allocation.hpp>
#include <cx/cpp.hpp>

namespace cx {

using Byte = cpp::uint8_t;
using Rune = cpp::int32_t;
using Int = int;
using Uint = unsigned int;
using Uint32 = unsigned int;
using Int64 = cpp::int64_t;
using Uint64 = cpp::uint64_t;
using UintPtr = cpp::uintptr_t;

template <typename F>
using Func = cpp::function<F>;

template <typename T>
void Panic(T v) {
    // TODO: ???
    __builtin_trap();
}

class String {
public:
    constexpr String() : _pos{0}, _len{0} {}

    String(const char* s) : String(s, cpp::strlen(s)) {}

    String(const char* s, cpp::size_t len) : _pos{0}, _len{Int(len)} {
        _data = allocation<Byte>(_len + 1);
        for (auto i = 0; i < _len; ++i) {
            _data[i] = s[i];
        }
        _data[_len] = 0;
    }

    constexpr Byte operator[](int i) const {
        if (i >= _len) {
            Panic("out of bounds");
        }
        return _data[_pos + i];
    }

    constexpr Int Len() const { return _len; }

    String operator+(String s) const {
        auto len = Len() + s.Len();
        allocation<Byte> data(len);
        for (auto i = 0; i < Len(); ++i) {
            data[i] = _data[_pos + i];
        }
        for (auto i = 0; i < s.Len(); ++i) {
            data[Len() + i] = s[i];
        }
        return String{data, 0, len};
    }

    bool operator==(String s) const {
        if (_len != s._len) {
            return false;
        }
        for (Int i = 0; i < _len; ++i) {
            if (_data[_pos + i] != s._data[s._pos + i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(String s) const {
        return !(*this == s);
    }

    String Head(Int end) const {
        if (end > _len) {
            Panic("out of bounds");
        }
        return String(_data, _pos, end);
    }

    String Tail(Int start) const {
        if (start > _len) {
            Panic("out of bounds");
        }
        return String(_data, _pos + start, _len - start);
    }

    // Returns a String object that's guaranteed to provide a null-terminated string when CString is
    // called.
    String NullTerminated() const {
        if (_len == 0) {
            return *this;
        }
        if (_data.count() >= _pos + _len && _data[_pos + _len] == 0) {
            return *this;
        }
        return String(CString(), _len);
    }

    // Returns a pointer to the underlying string. This is not guaranteed to be null terminated
    // unless this String is a result of a NullTerminated call.
    const char* CString() const {
        if (_len == 0) {
            return "";
        }
        return reinterpret_cast<const char*>(&_data[_pos]);
    }

private:
    String(allocation<Byte> data, Int pos, Int len) : _data{data}, _pos{pos}, _len{len} {}

    allocation<Byte> _data;
    Int _pos;
    Int _len;
};

template <typename T>
static String operator+(T prefix, String suffix) {
    return String(prefix) + suffix;
}

template <typename T>
class Slice {
public:
    constexpr Slice() {}

    explicit Slice(Int len) : _data(len), _len{len} {}

    explicit Slice(String s) : _data(s.Len()), _len{s.Len()} {
        for (auto i = 0; i < _len; ++i) {
            _data[i] = s[i];
        }
    }

    explicit operator String() const {
        if (!_len) { return {}; }
        return String(reinterpret_cast<const char*>(&_data[_pos]), _len);
    }

    constexpr T& operator[](int i) {
        if (i >= _len) {
            Panic("out of bounds");
        }
        return _data[_pos + i];
    }

    constexpr Int Len() const { return _len; }

    Slice Head(Int end) const {
        if (end > _len) {
            Panic("out of bounds");
        }
        return Slice(_data, _pos, end);
    }

    Slice Tail(Int start) const {
        if (start > _len) {
            Panic("out of bounds");
        }
        return Slice(_data, _pos + start, _len - start);
    }

private:
    Slice(allocation<T> data, Int pos, Int len)
        : _data{data}, _pos{pos}, _len{len} {}

    allocation<T> _data;
    Int _pos = 0;
    Int _len = 0;
};

class Error {
public:
    constexpr Error() {}

    template <typename T>
    constexpr Error(T err) : _error{err.Error()} {}

    explicit constexpr operator bool() const { return _error.Len() > 0; }
    explicit operator String() const { return _error; }
    bool operator==(const Error& other) const { return _error == other._error; }
    bool operator!=(const Error& other) const { return _error != other._error; }

private:
    String _error;
};

template <typename T>
class Ptr {
public:
    Ptr() {}

    template <typename... Args>
    static Ptr New(Args... args) {
        return Ptr(nullptr, args...);
    }

    T* operator->() const { return &_data[0]; }

    constexpr operator bool() const { return _data; }

private:
    template <typename... Args>
    Ptr(void*, Args... args) : _data{1, args...} {}

    allocation<T> _data;
};

template <typename T, typename... Args>
Ptr<T> New(Args... args) {
    return Ptr<T>::New(args...);
}

} // namespace cx
