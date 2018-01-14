#pragma once

#include <cx/cpp/cstdint.hpp>

namespace cx::cpp {

template <class T> struct remove_reference      { typedef T type; };
template <class T> struct remove_reference<T&>  { typedef T type; };
template <class T> struct remove_reference<T&&> { typedef T type; };

template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant type;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <class> struct is_function : false_type { };
template <class Ret, class... Args> struct is_function<Ret(Args...)> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...)> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile &> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile &&> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile & noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) volatile && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args...) const volatile && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) volatile && noexcept> : true_type {};
template <class Ret, class... Args> struct is_function<Ret(Args..., ...) const volatile && noexcept> : true_type {};

template <bool B, class T, class F> struct conditional { typedef T type; };
template <class T, class F> struct conditional<false, T, F> { typedef F type; };

template <class T> struct is_array : false_type {};
template <class T> struct is_array<T[]> : true_type {};
template <class T, size_t N> struct is_array<T[N]> : true_type {};

template <class T> struct remove_extent { typedef T type; };
template <class T> struct remove_extent<T[]> { typedef T type; };
template <class T, size_t N> struct remove_extent<T[N]> { typedef T type; };

namespace detail {
    template <class T, bool is_function_type = false>
    struct add_pointer {
        using type = typename remove_reference<T>::type*;
    };

    template <class T>
    struct add_pointer<T, true> {
        using type = T;
    };

    template <class T, class... Args>
    struct add_pointer<T(Args...), true> {
        using type = T(*)(Args...);
    };

    template <class T, class... Args>
    struct add_pointer<T(Args..., ...), true> {
        using type = T(*)(Args..., ...);
    };
}

template <class T> struct add_pointer : detail::add_pointer<T, is_function<T>::value> {};

template <class T> struct remove_const          { typedef T type; };
template <class T> struct remove_const<const T> { typedef T type; };

template <class T> struct remove_volatile             { typedef T type; };
template <class T> struct remove_volatile<volatile T> { typedef T type; };

template <class T>
struct remove_cv {
    typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

template <class T>
struct decay {
private:
    typedef typename remove_reference<T>::type U;
public:
    typedef typename conditional<
        is_array<U>::value,
        typename remove_extent<U>::type*,
        typename conditional<
            is_function<U>::value,
            typename add_pointer<U>::type,
            typename remove_cv<U>::type
        >::type
    >::type type;
};

} // namespace cx::cpp
