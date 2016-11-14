#pragma once
#include <random>
#include <chrono>

namespace m {
    // Produces an integer value evenly distributed across a range
    template <typename T, typename UniformRandomBitGenerator>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    UniformDistribution(T min, T max, UniformRandomBitGenerator&& g) {
        return std::uniform_int_distribution<T>(min, max)(g);
    }

    // Produces a real value evenly distributed across a range
    template <typename T, typename UniformRandomBitGenerator>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    UniformDistribution(T min, T max, UniformRandomBitGenerator&& g) {
        return std::uniform_real_distribution<T>(min, max)(g);
    }

    // Produces an arithmetic value evenly distributed across a range of mixed type arithmetic values
    template <typename T, typename U, typename UniformRandomBitGenerator>
    typename std::enable_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, typename std::common_type<T, U>::type>::type
    UniformDistribution(T min, U max, UniformRandomBitGenerator&& g) {
        using CommonType = typename std::common_type<T, U>::type;
        return UniformDistribution<CommonType>(static_cast<CommonType>(min), static_cast<CommonType>(max),
                                               std::forward<UniformRandomBitGenerator>(g));
    }

    // Produces a chrono::durartion value evenly distributed across a range
    template <typename Rep1, typename Period1, typename Rep2, typename Period2, typename UniformRandomBitGenerator>
    auto UniformDistribution(const std::chrono::duration<Rep1, Period1>& min,
                             const std::chrono::duration<Rep2, Period2>& max,
                             UniformRandomBitGenerator&& g)
    {
        using CommonType = typename std::common_type<std::chrono::duration<Rep1, Period1>,
                                                     std::chrono::duration<Rep2, Period2>>::type;
        return CommonType{UniformDistribution(CommonType{min}.count(), CommonType{max}.count(),
                                              std::forward<UniformRandomBitGenerator>(g))};
    }

    // Produces a chrono::time_point value evenly distributed across a range
    template <typename Clock, typename Duration1, typename Duration2, typename UniformRandomBitGenerator>
    auto UniformDistribution(const std::chrono::time_point<Clock, Duration1>& min,
                             const std::chrono::time_point<Clock, Duration2>& max,
                             UniformRandomBitGenerator&& g)
    {
        using CommonType = typename std::common_type<std::chrono::time_point<Clock, Duration1>,
                                                     std::chrono::time_point<Clock, Duration2>>::type;
        return CommonType{UniformDistribution(min.time_since_epoch(), max.time_since_epoch(),
                                              std::forward<UniformRandomBitGenerator>(g))};
    }
}
