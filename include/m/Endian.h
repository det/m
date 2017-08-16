#pragma once
#include <cstdint>
#include <type_traits>

namespace m {
    enum class Endian {
    #if __clang__ || __GNUC__
        little = __ORDER_LITTLE_ENDIAN__,
        big    = __ORDER_BIG_ENDIAN__,
        native = __BYTE_ORDER__
    #else
        little = 0,
        big    = 1,
        native = little
    #endif
    };

    constexpr uint16_t SwapByteOrder(uint16_t x) noexcept {
    #if __clang__ || __GNUC__
        return __builtin_bswap16(x);
    #else
        return (x >> 8) | (x << 8);
    #endif
    }

    constexpr int16_t SwapByteOrder(int16_t x) noexcept {
        return static_cast<int16_t>(SwapByteOrder(static_cast<uint16_t>(x)));
    }

    constexpr uint32_t SwapByteOrder(uint32_t x) noexcept {
    #if __clang__ || __GNUC__
        return __builtin_bswap32(x);
    #else
        return ((x << 24) & 0xff000000u) |
               ((x << 8)  & 0x00ff0000u) |
               ((x >> 8)  & 0x0000ff00u) |
               ((x >> 24) & 0x000000ffu);
    #endif
    }

    constexpr int32_t SwapByteOrder(int32_t x) noexcept {
        return static_cast<int32_t>(SwapByteOrder(static_cast<uint32_t>(x)));
    }

    constexpr uint64_t SwapByteOrder(uint64_t x) noexcept {
    #if __clang__ || __GNUC__
        return __builtin_bswap64(x);
    #else
        return ((x << 56) & 0xff00000000000000u) |
               ((x << 40) & 0x00ff000000000000u) |
               ((x << 24) & 0x0000ff0000000000u) |
               ((x << 8)  & 0x000000ff00000000u) |
               ((x >> 8)  & 0x00000000ff000000u) |
               ((x >> 24) & 0x0000000000ff0000u) |
               ((x >> 40) & 0x000000000000ff00u) |
               ((x >> 56) & 0x00000000000000ffu);
    #endif
    }

    constexpr int64_t SwapByteOrder(int64_t x) noexcept {
        return static_cast<int64_t>(SwapByteOrder(static_cast<uint64_t>(x)));
    }

    template <class T>
    constexpr T NativeToLittleEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return Endian::native != Endian::little ? SwapByteOrder(x) : x;
    }

    template <class T>
    constexpr T NativeToBigEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return Endian::native != Endian::big ? SwapByteOrder(x) : x;
    }

    template <class T>
    constexpr T LittleToNativeEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return Endian::little != Endian::native ? SwapByteOrder(x) : x;
    }

    template <class T>
    constexpr T BigToNativeEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return Endian::big != Endian::native ? SwapByteOrder(x) : x;
    }

    template <class T>
    constexpr T LittleToBigEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return SwapByteOrder(x);
    }

    template <class T>
    constexpr T BigToLittleEndian(T x) noexcept {
        static_assert(std::is_integral<T>::value && sizeof(x) > 1, "argument must be a multibyte integer");
        return SwapByteOrder(x);
    }
}
