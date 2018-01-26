#pragma once

#include <gostd/_string.hpp>
#include <gostd/_tuple.hpp>

namespace gostd {

template <typename T>
class Slice {
public:
    constexpr Slice() {}

    template <typename N, typename M = Int>
    static Slice<T> Make(N len, M cap = 0) {
        Slice<T> ret;
        ret._data = allocation<T>(Uint64(cap) >= Uint64(len) ? Uint64(cap) : Uint64(len));
        ret._len = Int(len);
        return ret;
    }

    template <typename... Rem>
    explicit Slice(T next, Rem&&... rem) : _data(1 + sizeof...(rem)), _len{1} {
        _data[0] = cpp::move(next);
        _append(cpp::forward<Rem>(rem)...);
    }

    template <typename U = T>
    explicit Slice(String s, typename cpp::enable_if<cpp::is_same<U, Byte>::value>::type* = 0) : _data(Uint64(s.len())), _len{s.len()} {
        for (Int i = 0; i < _len; i++) {
            _data[i] = s[i];
        }
    }

    explicit operator String() const {
        if (!_len) { return {}; }
        return String(reinterpret_cast<const char*>(&_data[_pos]), _len.value());
    }

    template <typename N>
    constexpr T& operator[](N i) {
        if (Int(i) >= _len) {
            Panic("out of bounds");
        }
        return _data[_pos + Int(i)];
    }

    template <typename N>
    constexpr const T& operator[](N i) const {
        if (Int(i) >= _len) {
            Panic("out of bounds");
        }
        return _data[_pos + Int(i)];
    }

    constexpr Int len() const { return _len; }
    constexpr Int cap() const { return Int(_data.count()) - _pos; }

    template <typename N>
    Slice Head(N end) const {
        if (Int(end) > cap()) {
            Panic("out of bounds");
        }
        return Slice(_data, _pos, Int(end));
    }

    template <typename N>
    Slice Tail(N start) const {
        if (Int(start) > _len) {
            Panic("out of bounds");
        }
        return Slice(_data, _pos + Int(start), _len - Int(start));
    }

    Slice _sliceWithSuffix(Slice<T> elements) const {
        if (cap() >= _len + elements.len()) {
            auto ret = Slice(_data, _pos, _len + elements.len());
            Copy(ret.Tail(_len), elements);
            return ret;
        }
        auto ret = Make(_len + elements.len(), _len + (_len >= elements.len() ? _len : elements.len()));
        Copy(ret, *this);
        Copy(ret.Tail(_len), elements);
        return ret;
    }

    Slice _sliceWithSuffix() const { return *this; }

    template <typename... Rem>
    Slice _sliceWithSuffix(T element, Rem&&... rem) const {
        if (cap() >= _len + 1 + sizeof...(rem)) {
            _data[_len] = cpp::move(element);
            return Slice(_data, _pos, _len + 1)._sliceWithSuffix(cpp::forward<Rem>(rem)...);
        }
        auto ret = Make(_len + 1, _len + (_len >= 1 + sizeof...(rem) ? _len : (1 + sizeof...(rem))));
        Copy(ret, *this);
        ret[_len] = cpp::move(element);
        return ret._sliceWithSuffix(cpp::forward<Rem>(rem)...);
    }

    struct iterator {
        Slice slice;
        Int offset;

        bool operator!=(const iterator& other) const { return offset == other.offset; }
        iterator& operator++() { offset++; return *this; }
        Tuple<Int, T> operator*() const {
            return {offset, slice[offset]};
        }
    };

    iterator begin() { return {*this, 0}; }
    iterator end() { return {*this, _len}; }

private:
    Slice(allocation<T> data, Int pos, Int len)
        : _data{data}, _pos{pos}, _len{len} {}

    void _append() {}

    template <typename... Rem>
    void _append(T next, Rem&&... rem) {
        _data[_len] = cpp::move(next);
        _len++;
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
