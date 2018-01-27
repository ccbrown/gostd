#pragma once

#include <gostd/cpp.hpp>

namespace gostd {

class UntypedConstant {
public:
    template <cpp::size_t N>
    constexpr explicit UntypedConstant(const char(&s)[N]) : _str{s}, _strlen(N - 1) {}

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, char x = 0) : _sign{n ? 1 : 0}, _abs{n} {}

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && !cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, void* x = 0) : _sign{n < 0 ? -1 : (n ? 1: 0)}, _abs{n < 0 ? cpp::uint64_t(-n) : n} {}

    constexpr cpp::uint64_t Abs() const { return _abs; }
    constexpr int Sign() const { return _sign; }

    constexpr const char* CString() const { return _str; }
    constexpr cpp::size_t CStringLength() const { return _strlen; }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator<(T right) const {
        if (cpp::is_unsigned<T>::value) {
            return _sign < 0 || _abs < right;
        } else if (_sign >= 0) {
            return right > 0 && cpp::uint64_t(right) > _abs;
        }
        return right >= 0 || cpp::uint64_t(-right) < _abs;
    }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator==(T right) const {
        if (cpp::is_unsigned<T>::value) {
            return _sign >= 0 && _abs == right;
        } if (_sign < 0) {
            return right < 0 && _abs == cpp::uint64_t(-right);
        }
        return right >= 0 && cpp::uint64_t(right) == _abs;
    }
    constexpr bool operator==(UntypedConstant right) const {
        if (_sign != right._sign || _abs != right._abs || _strlen != right._strlen) {
            return false;
        }
        for (cpp::size_t i = 0; i < _strlen; ++i) {
            if (_str[i] != right._str[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator!=(T right) const { return !(*this == right); }
    constexpr bool operator!=(UntypedConstant right) const { return !(*this == right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator>=(T right) const { return !(*this < right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator<=(T right) const { return !(*this > right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator>(T right) const { return *this >= right && *this != right; }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr auto operator+(T right) const { return *this + UntypedConstant(right); }

    constexpr UntypedConstant operator+(UntypedConstant right) const {
        if (_sign == 0) {
            return right;
        } else if (_sign == right._sign) {
            return UntypedConstant(_sign, _abs + right._abs);
        } else if (right._abs > _abs) {
            return UntypedConstant(-_sign, right._abs - _abs);
        } else if (right._abs < _abs) {
            return UntypedConstant(_sign, _abs - right._abs);
        }
        return UntypedConstant(0, 0);
    }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr auto operator&(T right) const { return UntypedConstant(_abs & right); }
    constexpr auto operator&(UntypedConstant right) const { return UntypedConstant(_abs & right._abs); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr auto operator|(T right) const { return UntypedConstant(_abs | right); }
    constexpr auto operator|(UntypedConstant right) const { return UntypedConstant(_abs | right._abs); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    explicit constexpr operator T() const { return _sign < 0 ? T(-_abs) : T(_abs); }

private:
    constexpr UntypedConstant(int sign, cpp::uint64_t abs) : _sign{sign}, _abs(abs) {}

    const int _sign = 0;
    const cpp::uint64_t _abs = 0;
    const char* const _str = nullptr;
    const cpp::size_t _strlen = 0;
};

template <typename T> constexpr bool operator<(T left, UntypedConstant right) { return right > left; }
template <typename T> constexpr bool operator>(T left, UntypedConstant right) { return right < left; }
template <typename T> constexpr bool operator<=(T left, UntypedConstant right) { return right >= left; }
template <typename T> constexpr bool operator>=(T left, UntypedConstant right) { return right <= left; }
template <typename T> constexpr bool operator==(T left, UntypedConstant right) { return right == left; }
template <typename T> constexpr bool operator!=(T left, UntypedConstant right) { return right != left; }

template <typename T, typename = typename cpp::enable_if<!cpp::is_same<T, UntypedConstant>::value>::type>
constexpr T operator&(T left, UntypedConstant right) { return right & left; }

template <typename T, typename = typename cpp::enable_if<!cpp::is_same<T, UntypedConstant>::value>::type>
constexpr T operator|(T left, UntypedConstant right) { return right | left; }

} // namespace gostd
