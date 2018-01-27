#pragma once

#include <gostd/_tuple.hpp>
#include <gostd/_untyped_constant.hpp>

namespace gostd {

class String {
public:
    constexpr String() : _pos{0}, _len{0} {}

    template <typename T, typename = typename cpp::enable_if<cpp::is_same<T, char*>::value || cpp::is_same<T, const char*>::value>::type>
    String(T s) : String(s, cpp::strlen(s)) {}

    template <cpp::size_t N>
    String(const char(&s)[N]) : String(s, N - 1) {}

    String(const char* s, cpp::size_t len) : _pos{0}, _len{Int(len)} {
        _data = allocation<Byte>(Uint64(_len) + 1);
        for (auto i = 0; i < _len; ++i) {
            _data[i] = s[i];
        }
        _data[_len] = 0;
    }

    String(UntypedConstant c) : String(c.CString(), c.CStringLength()) {}

    template <typename N>
    constexpr Byte operator[](N i) const {
        if (Int(i) >= _len) {
            Panic("out of bounds");
        }
        return _data[_pos + Int(i)];
    }

    constexpr Int len() const { return _len; }

    String operator+(String s) const {
        auto l = len() + s.len();
        allocation<Byte> data(Uint64(l) + 1);
        for (auto i = 0; i < len(); ++i) {
            data[i] = _data[_pos + i];
        }
        for (auto i = 0; i < s.len(); ++i) {
            data[len() + i] = s[i];
        }
        data[l] = 0;
        return String{data, 0, l};
    }

    bool operator==(String s) const {
        if (_len != s._len) {
            return false;
        }
        for (Int i = 0; i < _len; i++) {
            if (_data[_pos + i] != s._data[s._pos + i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(String s) const {
        return !(*this == s);
    }

    template <typename N>
    String Head(N end) const {
        if (Int(end) > _len) {
            Panic("out of bounds");
        }
        return String(_data, _pos, Int(end));
    }

    template <typename N>
    String Tail(N start) const {
        if (Int(start) > _len) {
            Panic("out of bounds");
        }
        return String(_data, _pos + Int(start), _len - Int(start));
    }

    // Returns a String object that's guaranteed to provide a null-terminated string when CString is
    // called.
    String NullTerminated() const {
        if (_len == 0) {
            return *this;
        }
        if (_data.count() >= Uint64(_pos + _len) && _data[_pos + _len] == 0) {
            return *this;
        }
        return String(CString(), _len.value());
    }

    // Returns a pointer to the underlying string. This is not guaranteed to be null terminated
    // unless this String is a result of a NullTerminated call.
    const char* CString() const {
        if (_len == 0) {
            return "";
        }
        return reinterpret_cast<const char*>(&_data[_pos]);
    }

    struct iterator {
        String* string;
        Int offset;

        bool operator!=(const iterator& other) const { return offset != other.offset; }
        iterator& operator++();
        Tuple<Int, Rune> operator*() const;
    };

    iterator begin() { return {this, 0}; }
    iterator end() { return {this, _len}; }

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
String uitoa(T v) {
    char buf[33] = {0};
    auto i = sizeof(buf) - 2;
    while (v >= 10) {
        buf[i] = Byte(v%10 + '0').value();
        --i;
        v /= 10;
    }
    buf[i] = Byte(v + '0').value();
    return buf + i;
}

template <typename T>
String itoa(T v) {
    if (v < 0) {
        return "-" + uitoa(-v);
    }
    return uitoa(v);
}

} // namespace gostd
