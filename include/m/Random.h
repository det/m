#pragma once
#include <m/TypeTraits.h>
#include <chrono>
#include <random>
#include <type_traits>

namespace m {
    // A helper utility on top of std::uniform_int_distribution and std::uniform_real_distribution which works with
    // interoperating integer and floating point types, durations, time_points, and iterators.
    template <class T, class U, class RNG>
    auto uniformDistribution(T min, U max, RNG&& g) {
        using CommonType = std::common_type_t<T, U>;

        if constexpr (std::is_integral_v<CommonType>)
            return std::uniform_int_distribution<CommonType>(min, max)(g);

        if constexpr (std::is_floating_point_v<CommonType>)
            return std::uniform_real_distribution<CommonType>(min, max)(g);

        if constexpr (is_duration_v<CommonType>)
            return CommonType{uniformDistribution(CommonType{min}.count(), CommonType{max}.count(), g)};

        if constexpr (is_time_point_v<CommonType>)
            return CommonType{uniformDistribution(min.time_since_epoch(), max.time_since_epoch(), g)};

        if constexpr (is_iterator_v<CommonType>) {
            if (auto len = std::distance(min, max); len > 1)
                std::advance(min, uniformDistribution(0, len - 1, g));
            return min;
        }
    }
}
