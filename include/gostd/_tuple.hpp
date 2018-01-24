#pragma once

namespace gostd {

template <typename First, typename... Rem>
class Tuple {
public:
    constexpr Tuple(First first, Rem... rem) : _element{cpp::move(first)}, _remaining{cpp::move(rem)...} {}

    static constexpr int Size = 1 + sizeof...(Rem);

    template <int I>
    using Type = typename cpp::conditional<I == 0, First, typename Tuple<Rem...>::template Type<I - 1>>::type;

    template <int I>
    constexpr auto Get() { return _get(cpp::integral_constant<int, I>{}); }

private:
    First _element;
    Tuple<Rem...> _remaining;

    constexpr auto _get(cpp::integral_constant<int, 0> i) { return _element; }

    template <typename I>
    constexpr auto _get(I i) { return _remaining.template Get<I::value - 1>(); }
};

template <typename T>
class Tuple<T> {
public:
    explicit Tuple(T element) : _element{cpp::move(element)} {}

    static constexpr int Size = 1;

    template <int i>
    using Type = T;

    template <int I>
    constexpr auto Get() {
        static_assert(I == 0, "index out of bounds");
        return _element;
    }

private:
    T _element;
};

template <cpp::size_t I, typename... Elements>
auto get(Tuple<Elements...> t) { return t.template Get<I>(); }

} // namespace gostd

namespace std {
    template <typename T> struct tuple_size;
    template <gostd::cpp::size_t I, typename T> struct tuple_element;

    template <typename... Elements>
    struct tuple_size<gostd::Tuple<Elements...>> {
        static constexpr int value = gostd::Tuple<Elements...>::Size;
    };

    template <gostd::cpp::size_t I, typename... Elements>
    struct tuple_element<I, gostd::Tuple<Elements...>> {
        using type = typename gostd::Tuple<Elements...>::template Type<I>;
    };
}
