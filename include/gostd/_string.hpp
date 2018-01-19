#pragma once

namespace gostd {

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

template <typename T>
String uitoa(T v) {
    char buf[33] = {0};
    auto i = sizeof(buf) - 2;
    while (v >= 10) {
        buf[i] = v%10 + '0';
        --i;
        v /= 10;
    }
    buf[i] = v + '0';
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
