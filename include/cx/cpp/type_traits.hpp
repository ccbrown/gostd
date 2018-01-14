#pragma once

#include <cx/cpp/cstdint.hpp>

namespace cx::cpp {

template <typename T> struct remove_reference      { typedef T type; };
template <typename T> struct remove_reference<T&>  { typedef T type; };
template <typename T> struct remove_reference<T&&> { typedef T type; };

template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant type;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename> struct is_function : false_type { };
template <typename Ret, typename... Args> struct is_function<Ret(Args...)> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...)> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile &> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile &&> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile & noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) volatile && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args...) const volatile && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) volatile && noexcept> : true_type {};
template <typename Ret, typename... Args> struct is_function<Ret(Args..., ...) const volatile && noexcept> : true_type {};

template <bool B, typename T, typename F> struct conditional { typedef T type; };
template <typename T, typename F> struct conditional<false, T, F> { typedef F type; };

template <typename T> struct is_array : false_type {};
template <typename T> struct is_array<T[]> : true_type {};
template <typename T, size_t N> struct is_array<T[N]> : true_type {};

template <typename T> struct remove_extent { typedef T type; };
template <typename T> struct remove_extent<T[]> { typedef T type; };
template <typename T, size_t N> struct remove_extent<T[N]> { typedef T type; };

namespace detail {
    template <typename T, bool is_function_type = false>
    struct add_pointer {
        using type = typename remove_reference<T>::type*;
    };

    template <typename T>
    struct add_pointer<T, true> {
        using type = T;
    };

    template <typename T, typename... Args>
    struct add_pointer<T(Args...), true> {
        using type = T(*)(Args...);
    };

    template <typename T, typename... Args>
    struct add_pointer<T(Args..., ...), true> {
        using type = T(*)(Args..., ...);
    };
}

template <typename T> struct add_pointer : detail::add_pointer<T, is_function<T>::value> {};

template <typename T> struct remove_const          { typedef T type; };
template <typename T> struct remove_const<const T> { typedef T type; };

template <typename T> struct remove_volatile             { typedef T type; };
template <typename T> struct remove_volatile<volatile T> { typedef T type; };

template <typename T>
struct remove_cv {
    typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

template <typename T>
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

template <bool B, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { typedef T type; };

template <typename T> struct remove_pointer                    { typedef T type; };
template <typename T> struct remove_pointer<T*>                { typedef T type; };
template <typename T> struct remove_pointer<T* const>          { typedef T type; };
template <typename T> struct remove_pointer<T* volatile>       { typedef T type; };
template <typename T> struct remove_pointer<T* const volatile> { typedef T type; };

template <typename T, typename U> struct is_same : false_type {};
template <typename T> struct is_same<T, T> : true_type {};

namespace detail {
    struct dummy {};

    struct is_referenceable_impl {
        template <typename T> static T& test(int);
        template <typename T> static dummy test(...);
    };

    template <typename T>
    struct is_referenceable : integral_constant<bool, !is_same<decltype(is_referenceable_impl::test<T>(0)), dummy>::value> {};

    template <typename T, bool = is_referenceable<T>::value> struct add_rvalue_reference { typedef T type; };
    template <typename T> struct add_rvalue_reference<T, true> { typedef T&& type; };
}

template <typename T> struct add_rvalue_reference { typedef typename detail::add_rvalue_reference<T>::type type; };

template <typename ...>
using void_t = void;

} // namespace cx::cpp
