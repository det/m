#pragma once
#include <random>
#include <chrono>
#include <type_traits>

namespace m {
    // Produces an arithmetic value evenly distributed across a range
    template <class T, class U, class RNG>
    std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, std::common_type_t<T, U>>
    UniformDistribution(T min, U max, RNG&& g) {
        using CommonType = std::common_type_t<T, U>;
        using DistributionType = std::conditional_t<
            std::is_integral<CommonType>::value,
            std::uniform_int_distribution<CommonType>,
            std::uniform_real_distribution<CommonType>
        >;
        return DistributionType(min, max)(g);
    }

    // Produces a chrono::durartion value evenly distributed across a range
    template <class Rep1, class Period1, class Rep2, class Period2, class RNG>
    auto UniformDistribution(const std::chrono::duration<Rep1, Period1>& min,
                             const std::chrono::duration<Rep2, Period2>& max,
                             RNG&& g)
    {
        using CommonType = std::common_type_t<
            std::chrono::duration<Rep1, Period1>,
            std::chrono::duration<Rep2, Period2>
        >;
        return CommonType{UniformDistribution(CommonType{min}.count(), CommonType{max}.count(), g)};
    }

    // Produces a chrono::time_point value evenly distributed across a range
    template <class Clock, class Duration1, class Duration2, class RNG>
    auto UniformDistribution(const std::chrono::time_point<Clock, Duration1>& min,
                             const std::chrono::time_point<Clock, Duration2>& max,
                             RNG&& g)
    {
        using CommonType = std::common_type_t<
            std::chrono::time_point<Clock, Duration1>,
            std::chrono::time_point<Clock, Duration2>
        >;
        return CommonType{UniformDistribution(min.time_since_epoch(), max.time_since_epoch(), g)};
    }
}

