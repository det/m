#pragma once
#include <chrono>
#include <iterator>
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
    }

    template <class F, size_t N = 0u, class = void>
    struct arity : arity<F, N + 1u, void> {};

    template <class F, size_t N>
    struct arity<F, N, std::enable_if_t<detail::CanCall<F, N>::value>> : std::integral_constant<size_t, N> {};

    template <class F>
    struct arity<F, 64, void> : std::integral_constant<size_t, 64> {};

    template <class F>
    constexpr size_t arity_v = arity<F>::value;

    // Whether the arity of a function is zero (function takes no arguments).
    // This will compile faster than calling arity<F> == 0, and it compiles with
    // lambdas which take auto arguments.
    template <class F>
    constexpr bool arity_zero = detail::CanCall<F, 0>::value;

    template <class T>
    struct is_duration : std::false_type {};

    template <class Rep, class Period>
    struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

    template <class Rep, class Period>
    struct is_duration<const std::chrono::duration<Rep, Period>> : std::true_type {};

    template <class Rep, class Period>
    struct is_duration<volatile std::chrono::duration<Rep, Period>> : std::true_type {};

    template <class Rep, class Period>
    struct is_duration<const volatile std::chrono::duration<Rep, Period>> : std::true_type {};

    template <class T>
    constexpr bool is_duration_v = is_duration<T>::value;

    template <class T>
    struct is_time_point : std::false_type {};

    template <class Clock, class Duration>
    struct is_time_point<std::chrono::time_point<Clock, Duration>> : std::true_type {};

    template <class Clock, class Duration>
    struct is_time_point<const std::chrono::time_point<Clock, Duration>> : std::true_type {};

    template <class Clock, class Duration>
    struct is_time_point<volatile std::chrono::time_point<Clock, Duration>> : std::true_type {};

    template <class Clock, class Duration>
    struct is_time_point<const volatile std::chrono::time_point<Clock, Duration>> : std::true_type {};

    template <class T>
    constexpr bool is_time_point_v = is_time_point<T>::value;

    template <class T, class = std::void_t<>>
    struct is_iterator : std::false_type {};

    template<class T>
    struct is_iterator<T, std::void_t<typename std::iterator_traits<std::remove_cv_t<T>>::value_type>> : std::true_type {};

    template <class T>
    constexpr bool is_iterator_v = is_iterator<T>::value;
}
