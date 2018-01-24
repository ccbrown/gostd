#pragma once

#include <gostd/cpp.hpp>

namespace gostd {

class UntypedConstant {
public:
    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, char x = 0) : _sign{n ? 1 : 0}, _abs{n} {}

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && !cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, void* x = 0) : _sign{n < 0 ? -1 : (n ? 1: 0)}, _abs{n < 0 ? cpp::uint64_t(-n) : n} {}

    constexpr cpp::uint64_t Abs() const { return _abs; }
    constexpr int Sign() const { return _sign; }

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

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator!=(T right) const { return !(*this == right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator>=(T right) const { return !(*this < right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator<=(T right) const { return !(*this > right); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator>(T right) const { return *this >= right && *this != right; }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr auto operator&(T right) const { return UntypedConstant(_abs & right); }
    constexpr auto operator&(UntypedConstant right) const { return UntypedConstant(_abs & right._abs); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr auto operator|(T right) const { return UntypedConstant(_abs | right); }
    constexpr auto operator|(UntypedConstant right) const { return UntypedConstant(_abs | right._abs); }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    explicit constexpr operator T() const { return _sign < 0 ? T(-_abs) : T(_abs); }

private:
    const int _sign = 0;
    const cpp::uint64_t _abs = 0;
};

template <typename T> constexpr bool operator<(T left, UntypedConstant right) { return right > left; }
template <typename T> constexpr bool operator>(T left, UntypedConstant right) { return right < left; }
template <typename T> constexpr bool operator<=(T left, UntypedConstant right) { return right >= left; }
template <typename T> constexpr bool operator>=(T left, UntypedConstant right) { return right <= left; }
template <typename T> constexpr bool operator==(T left, UntypedConstant right) { return right == left; }

template <typename T, typename = typename cpp::enable_if<!cpp::is_same<T, UntypedConstant>::value>::type>
constexpr T operator&(T left, UntypedConstant right) { return right & left; }

template <typename T, typename = typename cpp::enable_if<!cpp::is_same<T, UntypedConstant>::value>::type>
constexpr T operator|(T left, UntypedConstant right) { return right | left; }

} // namespace gostd
