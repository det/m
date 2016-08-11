#pragma once
#include <random>
#include <chrono>

namespace m {
    //  Produces integer values evenly distributed across a range
    template <class T, class U = T, class Generator>
    typename std::enable_if<std::is_integral<T>::value && std::is_integral<U>::value, typename std::common_type<T, U>::type>::type
    UniformDistribution(Generator& g, T min = 0, U max = std::numeric_limits<U>::max()) {
        return std::uniform_int_distribution<typename std::common_type<T, U>::type>(min, max)(g);
    }

    //  Produces real values evenly distributed across a range
    template <class T, class U = T, class Generator>
    typename std::enable_if<std::is_floating_point<T>::value && std::is_floating_point<U>::value, typename std::common_type<T, U>::type>::type
    UniformDistribution(Generator& g, T min = 0.0, U max = 1.0) {
        return std::uniform_real_distribution<typename std::common_type<T, U>::type>(min, max)(g);
    }

    //  Produces chrono::durartion values evenly distributed across a range
    template <class Rep1, class Period1, class Rep2, class Period2, class Generator>
    typename std::common_type<std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>::type
    UniformDistribution(Generator& g, const std::chrono::duration<Rep1, Period1>& min, const std::chrono::duration<Rep2, Period2>& max) {
        using CommonType = typename std::common_type<std::chrono::duration<Rep1, Period1>, std::chrono::duration<Rep2, Period2>>::type;
        return CommonType{UniformDistribution(g, CommonType{min}.count(), CommonType{max}.count())};
    }

    //  Produces chromo::time_point values evenly distributed across a range
    template <class Clock, class Duration1, class Duration2, class Generator>
    typename std::common_type<std::chrono::time_point<Clock, Duration1>, std::chrono::time_point<Clock, Duration2>>::type
    UniformDistribution(Generator& g, const std::chrono::time_point<Clock, Duration1>& min, const std::chrono::time_point<Clock, Duration2>& max) {
        using CommonType = typename std::common_type<std::chrono::time_point<Clock, Duration1>, std::chrono::time_point<Clock, Duration2>>::type;
        return CommonType{min} + UniformDistribution(g, CommonType::duration::zero(), CommonType{max} - CommonType{min});
    }
}
