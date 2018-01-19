#pragma once

namespace gostd {

class UntypedConstant {
public:
    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, Uint64 x = 0) : _sign{n ? 1 : 0}, _abs{n} {}

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value && !cpp::is_unsigned<T>::value>::type>
    constexpr explicit UntypedConstant(T n, Int64 x = 0) : _sign{n < 0 ? -1 : (n ? 1: 0)}, _abs{n < 0 ? Uint64(-n) : n} {}

    constexpr Uint64 Abs() const { return _abs; }
    constexpr int Sign() const { return _sign; }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator<(T right) const {
        if (cpp::is_unsigned<T>::value) {
            return _sign < 0 || _abs < right;
        } else if (_sign >= 0) {
            return right > 0 && Uint64(right) > _abs;
        }
        return right >= 0 || Uint64(-right) < _abs;
    }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr bool operator==(T right) const {
        if (cpp::is_unsigned<T>::value) {
            return _sign >= 0 && _abs == right;
        } if (_sign < 0) {
            return right < 0 && _abs == Uint64(-right);
        }
        return right >= 0 && Uint64(right) == _abs;
    }

    template <typename T>
    constexpr bool operator!=(T right) const { return !(*this == right); }

    template <typename T>
    constexpr bool operator>=(T right) const { return !(*this < right); }

    template <typename T>
    constexpr bool operator<=(T right) const { return !(*this > right); }

    template <typename T>
    constexpr bool operator>(T right) const { return *this >= right && *this != right; }

    template <typename T>
    constexpr T operator&(T right) const { return T(*this) & right; }

    template <typename T>
    constexpr T operator|(T right) const { return T(*this) | right; }

    template <typename T>
    constexpr T operator-(T right) const { return T(*this) - right; }

    template <typename T>
    constexpr T operator+(T right) const { return T(*this) + right; }

    template <typename T, typename = typename cpp::enable_if<cpp::is_integral<T>::value>::type>
    constexpr operator T() const { return _sign < 0 ? T(-_abs) : T(_abs); }

private:
    const int _sign = 0;
    const Uint64 _abs = 0;
};

template <typename T>
constexpr bool operator<(T left, UntypedConstant right) { return right > left; }

template <typename T>
constexpr bool operator>(T left, UntypedConstant right) { return right < left; }

template <typename T>
constexpr bool operator<=(T left, UntypedConstant right) { return right >= left; }

template <typename T>
constexpr bool operator>=(T left, UntypedConstant right) { return right <= left; }

template <typename T>
constexpr bool operator==(T left, UntypedConstant right) { return right == left; }

template <typename T>
constexpr T operator&(T left, UntypedConstant right) { return right & left; }

template <typename T>
constexpr T operator|(T left, UntypedConstant right) { return right | left; }

template <typename T>
constexpr T operator-(T left, UntypedConstant right) { return left - T(right); }

template <typename T>
constexpr T operator+(T left, UntypedConstant right) { return right + left; }

} // namespace gostd
