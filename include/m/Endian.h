#pragma once
#include <type_traits>
#include <cstdint>

#if !(__clang__ || __GNUC__)
    #error clang or gcc required for endianness conversions
#endif

namespace m {
    enum class Endian
    {
        kNative = __BYTE_ORDER__,
        kLittle = __ORDER_LITTLE_ENDIAN__,
        kBig    = __ORDER_BIG_ENDIAN__
    };

    constexpr uint8_t  SwapByteOrder(uint8_t  x) noexcept { return x; }
    constexpr int8_t   SwapByteOrder(int8_t   x) noexcept { return x; }
    constexpr uint16_t SwapByteOrder(uint16_t x) noexcept { return __builtin_bswap16(x); }
    constexpr int16_t  SwapByteOrder(int16_t  x) noexcept { return static_cast<int16_t>(SwapByteOrder(static_cast<uint16_t>(x))); }
    constexpr uint32_t SwapByteOrder(uint32_t x) noexcept { return __builtin_bswap32(x); }
    constexpr int32_t  SwapByteOrder(int32_t  x) noexcept { return static_cast<int32_t>(SwapByteOrder(static_cast<uint32_t>(x))); }
    constexpr uint64_t SwapByteOrder(uint64_t x) noexcept { return __builtin_bswap64(x); }
    constexpr int64_t  SwapByteOrder(int64_t  x) noexcept { return static_cast<int64_t>(SwapByteOrder(static_cast<uint64_t>(x))); }

    namespace detail {
        template <typename T>
        constexpr T MaybeSwapByteOrder(T x, std::false_type) noexcept { return x; }

        template <typename T>
        constexpr T MaybeSwapByteOrder(T x, std::true_type) noexcept { return SwapByteOrder(x); }
    }

    template <typename T>
    constexpr T NativeToLittleEndian(T x) noexcept {
        return detail::MaybeSwapByteOrder(x, std::integral_constant<bool, Endian::kNative != Endian::kLittle>{});
    }

    template <typename T>
    constexpr T NativeToBigEndian(T x) noexcept {
        return detail::MaybeSwapByteOrder(x, std::integral_constant<bool, Endian::kNative != Endian::kBig>{});
    }

    template <typename T>
    constexpr T LittleToNativeEndian(T x) noexcept {
        return detail::MaybeSwapByteOrder(x, std::integral_constant<bool, Endian::kLittle != Endian::kNative>{});
    }

    template <typename T>
    constexpr T BigToNativeEndian(T x) noexcept {
        return detail::MaybeSwapByteOrder(x, std::integral_constant<bool, Endian::kBig != Endian::kNative>{});
    }

    template <typename T>
    constexpr T BigToLittleEndian(T x) noexcept {
        return SwapByteOrder(x);
    }

    template <typename T>
    constexpr T LittleToBigEndian(T x) noexcept {
        return SwapByteOrder(x);
    }
}
