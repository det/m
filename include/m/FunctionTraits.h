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

        template <class F, size_t N, size_t... I>
        struct CanCall<F, N, std::index_sequence<I...>, std::void_t<decltype(std::declval<F>()((static_cast<void>(I), std::declval<const Any&&>())...))>> : std::true_type {};
        
        template <class F, size_t N = 0u, class = void>
        struct Arity : Arity<F, N + 1u, void> {};
        
        template <class F, size_t N>
        struct Arity<F, N, std::enable_if_t<detail::CanCall<F, N>::value>> : std::integral_constant<size_t, N> {};
        
        template <class F>
        struct Arity<F, 64, void> : std::integral_constant<size_t, 64> {};
    }

    // The number of arguments a function takes (up to 64).
    template <class F>
    constexpr size_t arity = detail::Arity<F>::value;
    
    // Whether the arity of a function is zero (function takes no arguments).
    // This will compile faster than calling arity<F> == 0, and it compiles with
    // lambdas which take auto arguments.
    template <class F>
    constexpr bool arity_zero = detail::CanCall<F, 0>::value;
}
