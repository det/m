#pragma once
#include <type_traits>

namespace m {
    constexpr double pi     = 3.14159265358979323846;
    constexpr double e      = 2.71828182845904523540;
    constexpr double log2e  = 1.44269504088896340740;
    constexpr double log10e = 0.43429448190325182765;
    constexpr double ln2    = 0.69314718055994530942;
    constexpr double ln10   = 2.30258509299404568402;
    constexpr double sqrt2  = 1.41421356237309504880; // √2
    constexpr double sqrtpi = 1.77245385090551602729; // √π

    template <class T>
    constexpr bool ispow2(T n) noexcept {
        static_assert(std::is_unsigned_v<T>);
        return n != 0 && (n & (n-1)) == 0;
    }
}
