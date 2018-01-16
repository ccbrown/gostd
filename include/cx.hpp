#pragma once

#include <cx/allocation.hpp>
#include <cx/cpp.hpp>

namespace cx {

using Byte = cpp::uint8_t;
using Rune = cpp::int32_t;
using Uint8 = cpp::uint8_t;
using Uint16 = cpp::uint16_t;
using Int = int;
using Uint = unsigned int;
using Uint32 = cpp::uint32_t;
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
        allocation<Byte> data(len + 1);
        for (auto i = 0; i < Len(); ++i) {
            data[i] = _data[_pos + i];
        }
        for (auto i = 0; i < s.Len(); ++i) {
            data[Len() + i] = s[i];
        }
        data[len] = 0;
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

template <typename Destination, typename Source>
Int Copy(Destination dst, Source src) {
    auto count = (dst.Len() < src.Len() ? dst.Len() : src.Len());
    if (count > 0 && &dst[0] > &src[0] && &dst[0] <= &src[count-1]) {
        for (Int i = count - 1; i >= 0; --i) {
            dst[i] = src[i];
        }
    } else {
        for (Int i = 0; i < count; ++i) {
            dst[i] = src[i];
        }
    }
    return count;
}

template <typename T>
class Slice {
public:
    constexpr Slice() {}

    explicit Slice(Int len, Int cap = 0) : _data(cap >= len ? cap : len), _len{len} {}

    explicit Slice(String s) : _data(s.Len()), _len{s.Len()} {
        for (Int i = 0; i < _len; ++i) {
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
    constexpr Int Cap() const { return _data.count() - _pos; }

    Slice Head(Int end) const {
        if (end > Cap()) {
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

    Slice _sliceWithSuffix(Slice<T> elements) const {
        if (Cap() >= _len + elements.Len()) {
            auto ret = Slice(_data, _pos, _len + elements.Len());
            Copy(ret.Tail(_len), elements);
            return ret;
        }
        auto ret = Slice(_len + elements.Len(), _len + (_len >= elements.Len() ? _len : elements.Len()));
        Copy(ret, *this);
        Copy(ret.Tail(_len), elements);
        return ret;
    }

    Slice _sliceWithSuffix(T element) const {
        if (Cap() >= _len + 1) {
            _data[_len] = cpp::move(element);
            return Slice(_data, _pos, _len + 1);
        }
        auto ret = Slice(_len + 1, _len * 2);
        Copy(ret, *this);
        ret[_len] = cpp::move(element);
        return ret;
    }

private:
    Slice(allocation<T> data, Int pos, Int len)
        : _data{data}, _pos{pos}, _len{len} {}

    allocation<T> _data;
    Int _pos = 0;
    Int _len = 0;
};

template <typename T, typename... Args>
auto Append(Slice<T> slice, Args&&... args) {
    return slice._sliceWithSuffix(cpp::forward<Args>(args)...);
}

class Error {
public:
    constexpr Error() {}
    Error(const Error& other) = default;
    Error(Error&& other) = default;
    Error& operator=(const Error& other) = default;
    Error& operator=(Error&& other) = default;

    template <typename T, typename = typename cpp::enable_if<!cpp::is_same<typename cpp::decay<T>::type, Error>::value>::type>
    constexpr Error(T&& err) : Error(cpp::forward<T>(err), typename from_value_or_pointer<typename cpp::decay<T>::type>::type{}) {}

    explicit constexpr operator bool() const {
        return _error.has_value();
    }

    explicit operator String() const {
        if (!_errorFunc) {
            return "<nil>";
        }
        return _errorFunc();
    }
    bool operator==(const Error& other) const { return _error == other._error; }
    bool operator!=(const Error& other) const { return _error != other._error; }

    template <typename T>
    auto As() const {
        struct { T v; bool ok = false; } ret;
        if (auto ptr = cpp::any_cast<T>(&_error); ptr != nullptr) {
            ret.v = *ptr;
            ret.ok = true;
        }
        return ret;
    }

private:
    struct from_value {};
    struct from_pointer {};

    template <typename T>
    struct from_value_or_pointer {
        template <typename U> static from_value test(decltype(&U::Error));
        template <typename U> static from_pointer test(...);
        using type = decltype(test<T>(0));
    };

    template <typename T>
    Error(T&& err, from_value x) : _error{cpp::forward<T>(err)} {
        auto stored = cpp::any_cast<typename cpp::decay<T>::type>(&_error);
        _errorFunc = [=] { return stored->Error(); };
    }

    template <typename T>
    Error(T&& err, from_pointer x) : _error{cpp::forward<T>(err)} {
        auto stored = cpp::any_cast<typename cpp::decay<T>::type>(&_error);
        _errorFunc = [=] { return (*stored)->Error(); };
    }

    Func<String()> _errorFunc;
    cpp::any _error;
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

    T& operator *() { return _data[0]; }
    const T& operator *() const { return _data[0]; }

private:
    template <typename... Args>
    Ptr(void*, Args... args) : _data{1, args...} {}

    allocation<T> _data;
};

template <typename T, typename... Args>
Ptr<T> New(Args... args) {
    return Ptr<T>::New(args...);
}

class Defer {
public:
    explicit Defer(Func<void()> f) : _f{cpp::move(f)} {}
    ~Defer() { _f(); }

private:
    Func<void()> _f;
};

} // namespace cx
