#pragma once
#include <type_traits>
#include <utility>

namespace m {
    namespace detail {
        struct Any {
            template <class T> operator T&() const;
            template <class T> operator T&&() const;
        };

        template <class, size_t N, class = std::make_index_sequence<N>, class = void>
        struct CanCall : std::false_type {};

        template <class F, size_t N, size_t... Idx>
        struct CanCall<F, N, std::index_sequence<Idx...>, std::void_t<decltype(std::declval<F>()((Idx, std::declval<Any const&&>())...))>> : std::true_type {};
    }

    template <class F, size_t N = 0u, class = void>
    struct arity : arity<F, N + 1u, void> {};

    template <class F, size_t N>
    struct arity<F, N, std::enable_if_t<detail::CanCall<F, N>::value>> : std::integral_constant<size_t, N> {};

    template <class F>
    struct arity<F, 64, void> : std::integral_constant<size_t, 64> {};

    template <class F>
    constexpr auto arity_v = arity<F>::value;
}
