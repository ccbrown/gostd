#pragma once

#include <cx/cpp/cstdint.hpp>

namespace cx::cpp {

namespace detail {
    template <size_t Index>
    using index_constant = integral_constant<size_t, Index>;

    struct universal_value {
        size_t index;
        template <typename T> constexpr operator T&() const noexcept;
    };

    template <typename T, size_t... I>
    constexpr auto construct_with_value_count(index_sequence<I...>) noexcept
        -> typename add_pointer<decltype(T{universal_value{I}...})>::type;

    template <typename T, size_t N, typename = decltype(construct_with_value_count<T>(make_index_sequence<N>()))>
    using enable_if_constructible_with_value_count_t = size_t;

    template <class T, size_t N>
    constexpr auto n_if_constructible_with_value_count(index_constant<N>, long) noexcept -> enable_if_constructible_with_value_count_t<T, N> {
        return N;
    }

    template <class T, size_t N>
    constexpr size_t n_if_constructible_with_value_count(index_constant<N>, int) noexcept {
        return 0;
    }

    template <class T, size_t LastGuess>
    constexpr size_t field_count(index_constant<LastGuess>, index_constant<LastGuess>) noexcept {
        return n_if_constructible_with_value_count<T>(index_constant<LastGuess>{}, 1L);
    }

    template <class T, size_t Min, size_t Max>
    constexpr size_t field_count(index_constant<Min>, index_constant<Max>) noexcept {
        constexpr size_t middle = Min + (Max - Min) / 2;
        if (constexpr size_t count = field_count<T>(index_constant<middle + 1>{}, index_constant<Max>{}); count) {
            return count;
        }
        return field_count<T>(index_constant<Min>{}, index_constant<middle>{});
    }
} // namespace detail

template <typename T>
constexpr size_t field_count() noexcept {
    using T2 = typename remove_cv<T>::type;
    return detail::field_count<T2>(detail::index_constant<0>{}, detail::index_constant<sizeof(T2) * 8>{});
}

namespace detail {
    template <typename Next, typename... Rem>
    constexpr auto& get_arg(index_constant<0> i, Next&& next, Rem&&... rem) {
        return next;
    }

    template <typename I, typename Next, typename... Rem>
    constexpr auto& get_arg(I i, Next&& next, Rem&&... rem) {
        return get_arg(index_constant<i - 1>{}, forward<Rem>(rem)...);
    }

#define CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(n, ...) \
    template <size_t _I, typename _T> \
    constexpr auto& get_field(_T&& object, index_constant<n> count) noexcept { \
        auto& [__VA_ARGS__] = object; \
        return get_arg(index_constant<_I>{}, __VA_ARGS__); \
    }

    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(1, a)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(2, a, b)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(3, a, b, c)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(4, a, b, c, d)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(5, a, b, c, d, e)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(6, a, b, c, d, e, f)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(7, a, b, c, d, e, f, g)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(8, a, b, c, d, e, f, g, h)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(9, a, b, c, d, e, f, g, h, i)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(10, a, b, c, d, e, f, g, h, i, j)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(11, a, b, c, d, e, f, g, h, i, j, k)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(12, a, b, c, d, e, f, g, h, i, j, k, l)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(13, a, b, c, d, e, f, g, h, i, j, k, l, m)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(14, a, b, c, d, e, f, g, h, i, j, k, l, m, n)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(15, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(16, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(17, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(18, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(19, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(20, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(21, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(22, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(23, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(24, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(25, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(26, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(27, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(28, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(29, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(30, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(31, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(32, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(33, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(34, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(35, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(36, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(37, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(38, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(39, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(40, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(41, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(42, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(43, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(44, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(45, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(46, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(47, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(48, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(49, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(50, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(51, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y)
    CX_CPP_REFLECT_FIELD_COUNT_SUPPORT(52, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z)

} // namespace detail

template <size_t I, typename T>
auto& get_field(T&& object) {
    return detail::get_field<I>(forward<T>(object), detail::index_constant<field_count<typename remove_reference<T>::type>()>{});
}

template <size_t I, typename T>
struct field {
    using type = typename remove_reference<decltype(get_field<I>(declval<T>()))>::type;
};

} // namespace cx::cpp
