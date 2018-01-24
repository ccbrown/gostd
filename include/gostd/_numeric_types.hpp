#pragma once

#include <gostd/_untyped_constant.hpp>
#include <gostd/cpp.hpp>

namespace gostd {

template <typename T, typename Tag = void>
class NumericType {
public:
    constexpr NumericType() : _value{0} {}
    constexpr NumericType(T v) : _value{v} {}

    constexpr NumericType(UntypedConstant c) : _value{c} {}

    constexpr void operator=(T v) { _value = v; }

    template <typename U, typename UTag>
    explicit constexpr operator NumericType<U, UTag>() const { return NumericType<U, UTag>(_value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    explicit constexpr operator U() const { return U(_value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator<(U v) const { return _value < v; }
    constexpr bool operator<(NumericType n) const { return _value < n; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator>(U v) const { return _value > v; }
    constexpr bool operator>(NumericType n) const { return _value > n; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator<=(U v) const { return _value <= v; }
    constexpr bool operator<=(NumericType n) const { return _value <= n; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator>=(U v) const { return _value >= v; }
    constexpr bool operator>=(NumericType n) const { return _value >= n; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator==(U v) const { return _value == v; }
    constexpr bool operator==(NumericType n) const { return _value == n; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr bool operator!=(U v) const { return _value != v; }
    constexpr bool operator!=(NumericType n) const { return _value != n; }

    constexpr void operator--(int) { --_value; }
    constexpr void operator++(int) { ++_value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator-(U v) const { return NumericType(_value-v); }
    constexpr NumericType operator-(NumericType n) const { return NumericType(_value-n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator+(U v) const { return NumericType(_value+v); }
    constexpr NumericType operator+(NumericType n) const { return NumericType(_value+n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator*(U v) const { return NumericType(_value*v); }
    constexpr NumericType operator*(NumericType n) const { return NumericType(_value*n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator/(U v) const { return NumericType(_value/v); }
    constexpr NumericType operator/(NumericType n) const { return NumericType(_value/n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator%(U v) const { return NumericType(_value%v); }
    constexpr NumericType operator%(NumericType n) const { return NumericType(_value%n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator&(U v) const { return NumericType(_value&v); }
    constexpr NumericType operator&(NumericType n) const { return NumericType(_value&n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator|(U v) const { return NumericType(_value|v); }
    constexpr NumericType operator|(NumericType n) const { return NumericType(_value|n._value); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator>>(U v) const { return NumericType(_value>>v); }

    template <typename U, typename UTag>
    constexpr NumericType operator>>(NumericType<U, UTag> n) const { return NumericType(_value>>n.value()); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr NumericType operator<<(U v) const { return NumericType(_value<<v); }

    template <typename U, typename UTag>
    constexpr NumericType operator<<(NumericType<U, UTag> n) const { return NumericType(_value<<n.value()); }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator+=(U v) { _value += v; }
    constexpr void operator+=(NumericType n) { _value += n._value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator-=(U v) { _value -= v; }
    constexpr void operator-=(NumericType n) { _value -= n._value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator*=(U v) { _value *= v; }
    constexpr void operator*=(NumericType n) { _value *= n._value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator/=(U v) { _value /= v; }
    constexpr void operator/=(NumericType n) { _value /= n._value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator&=(U v) { _value &= v; }
    constexpr void operator&=(NumericType n) { _value &= n._value; }

    template <typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
    constexpr void operator|=(U v) { _value |= v; }
    constexpr void operator|=(NumericType n) { _value |= n._value; }

    constexpr NumericType operator-() const { return NumericType(-_value); }
    constexpr NumericType operator~() const { return NumericType(~_value); }

    constexpr T& value() { return _value; }
    constexpr T value() const { return _value; }

    template <typename TypeTag> using Type = NumericType<T, TypeTag>;

    using ValueType = T;

private:
    T _value;
};

template <typename T, typename Tag> constexpr bool operator<(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} < n; }
template <typename T, typename Tag> constexpr bool operator<(T v, NumericType<T, Tag> n) { return n > v; }
template <typename T, typename Tag> constexpr bool operator>(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} > n; }
template <typename T, typename Tag> constexpr bool operator>(T v, NumericType<T, Tag> n) { return n < v; }
template <typename T, typename Tag> constexpr bool operator<=(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} <= n; }
template <typename T, typename Tag> constexpr bool operator<=(T v, NumericType<T, Tag> n) { return n >= v; }
template <typename T, typename Tag> constexpr bool operator>=(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} >= n; }
template <typename T, typename Tag> constexpr bool operator>=(T v, NumericType<T, Tag> n) { return n <= v; }
template <typename T, typename Tag> constexpr bool operator==(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} == n; }
template <typename T, typename Tag> constexpr bool operator==(T v, NumericType<T, Tag> n) { return n == v; }
template <typename T, typename Tag> constexpr bool operator!=(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>{c} != n; }
template <typename T, typename Tag> constexpr bool operator!=(T v, NumericType<T, Tag> n) { return n != v; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator-(U v, NumericType<T, Tag> n) { return NumericType<T, Tag>{v} - n; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator+(U v, NumericType<T, Tag> n) { return n + v; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator*(U v, NumericType<T, Tag> n) { return n * v; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator/(U v, NumericType<T, Tag> n) { return NumericType<T, Tag>{v} / n; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator&(U v, NumericType<T, Tag> n) { return n & v; }

template <typename T, typename Tag>
constexpr NumericType<T, Tag> operator&(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>(c) & n; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator|(U v, NumericType<T, Tag> n) { return n | v; }

template <typename T, typename Tag>
constexpr NumericType<T, Tag> operator|(UntypedConstant c, NumericType<T, Tag> n) { return NumericType<T, Tag>(c) | n; }

template <typename T, typename Tag, typename U, typename = typename cpp::enable_if<cpp::is_integral<U>::value>::type>
constexpr NumericType<T, Tag> operator%(U v, NumericType<T, Tag> n) { return NumericType<T, Tag>{v} % n; }

using Bool = bool;
using Uint8 = NumericType<cpp::uint8_t>;
using Byte = Uint8;
using Uint16 = NumericType<cpp::uint16_t>;
using Int = NumericType<int>;
using Int32 = NumericType<cpp::int32_t>;
using Rune = Int32;
using Uint = NumericType<unsigned int>;
using Uint32 = NumericType<cpp::uint32_t>;
using Int64 = NumericType<cpp::int64_t>;
using Uint64 = NumericType<cpp::uint64_t>;
using UintPtr = NumericType<cpp::uintptr_t>;

template <typename T>
struct IsNumericType : cpp::false_type {};

template <typename T, typename Tag>
struct IsNumericType<NumericType<T, Tag>> : cpp::true_type {};

} // namespace gostd
