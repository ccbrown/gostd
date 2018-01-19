#pragma once

#include <gostd/_string.hpp>

namespace gostd {

template <typename T>
class Slice {
public:
    constexpr Slice() {}

    explicit Slice(Int len, Int cap = 0) : _data(cap >= len ? cap : len), _len{len} {}

    template <typename... Rem>
    explicit Slice(T next, Rem&&... rem) : _data(1 + sizeof...(rem)), _len{1} {
        _data[0] = cpp::move(next);
        _append(cpp::forward<Rem>(rem)...);
    }

    template <typename U = T>
    explicit Slice(String s, typename cpp::enable_if<cpp::is_same<U, Byte>::value>::type* = 0) : _data(s.Len()), _len{s.Len()} {
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

    Slice _sliceWithSuffix() const { return *this; }

    template <typename... Rem>
    Slice _sliceWithSuffix(T element, Rem&&... rem) const {
        if (Cap() >= _len + 1 + sizeof...(rem)) {
            _data[_len] = cpp::move(element);
            return Slice(_data, _pos, _len + 1)._sliceWithSuffix(cpp::forward<Rem>(rem)...);
        }
        auto ret = Slice(_len + 1, _len + (_len >= 1 + sizeof...(rem) ? _len : (1 + sizeof...(rem))));
        Copy(ret, *this);
        ret[_len] = cpp::move(element);
        return ret._sliceWithSuffix(cpp::forward<Rem>(rem)...);
    }

private:
    Slice(allocation<T> data, Int pos, Int len)
        : _data{data}, _pos{pos}, _len{len} {}

    void _append() {}

    template <typename... Rem>
    void _append(T next, Rem&&... rem) {
        _data[_len++] = cpp::move(next);
        _append(cpp::forward<Rem>(rem)...);
    }

    allocation<T> _data;
    Int _pos = 0;
    Int _len = 0;
};

template <typename T, typename... Args>
auto Append(Slice<T> slice, Args&&... args) {
    return slice._sliceWithSuffix(cpp::forward<Args>(args)...);
}

} // namespace gostd
