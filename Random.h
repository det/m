#pragma once
#include <random>
#include <chrono>

namespace m {
    // Produces integer values evenly distributed across a range
    template <typename T, typename U = T, typename Generator>
    typename std::enable_if<std::is_integral<T>::value && std::is_integral<U>::value, typename std::common_type<T, U>::type>::type
    UniformDistribution(Generator& g, T min = 0, U max = std::numeric_limits<U>::max()) {
        return std::uniform_int_distribution<typename std::common_type<T, U>::type>(min, max)(g);
    }

    // Produces real values evenly distributed across a range
    template <typename T, typename U = T, typename Generator>
    typename std::enable_if<std::is_floating_point<T>::value && std::is_floating_point<U>::value, typename std::common_type<T, U>::type>::type
    UniformDistribution(Generator& g, T min = 0.0, U max = 1.0) {
        return std::uniform_real_distribution<typename std::common_type<T, U>::type>(min, max)(g);
    }

    // Produces chrono::durartion values evenly distributed across a range
    template <typename Rep1, typename Period1, typename Rep2, typename Period2, typename Generator>
    typename std::common_type<std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>::type
    UniformDistribution(Generator& g, const std::chrono::duration<Rep1, Period1>& min, const std::chrono::duration<Rep2, Period2>& max) {
        using CommonType = typename std::common_type<std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>::type;
        return CommonType{UniformDistribution(g, CommonType{min}.count(), CommonType{max}.count())};
    }

    // Produces chromo::time_point values evenly distributed across a range
    template <typename Clock, typename Duration1, typename Duration2, typename Generator>
    typename std::common_type<std::chrono::time_point<Clock, Duration1>, std::chrono::time_point<Clock, Duration2>>::type
    UniformDistribution(Generator& g, const std::chrono::time_point<Clock, Duration1>& min, const std::chrono::time_point<Clock, Duration2>& max) {
        using CommonType = typename std::common_type<std::chrono::time_point<Clock, Duration1>, std::chrono::time_point<Clock, Duration2>>::type;
        return min + UniformDistribution(g, CommonType::duration::zero(), max - min);
    }
}
