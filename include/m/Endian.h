#pragma once
#include <cstdint>
#include <type_traits>

#if !__clang__ && !__GNUC__
    #error endian swapping currently only implemented for clang and gcc
#endif

namespace m {
    enum class Endian {
        little = __ORDER_LITTLE_ENDIAN__,
        big    = __ORDER_BIG_ENDIAN__,
        native = __BYTE_ORDER__
    };

    constexpr uint16_t SwapByteOrder(uint16_t x) noexcept { return __builtin_bswap16(x); }
    constexpr int16_t  SwapByteOrder(int16_t x) noexcept  { return static_cast<int16_t>(SwapByteOrder(static_cast<uint16_t>(x))); }
    constexpr uint32_t SwapByteOrder(uint32_t x) noexcept { return __builtin_bswap32(x); }
    constexpr int32_t  SwapByteOrder(int32_t x) noexcept  { return static_cast<int32_t>(SwapByteOrder(static_cast<uint32_t>(x))); }
    constexpr uint64_t SwapByteOrder(uint64_t x) noexcept { return __builtin_bswap64(x); }
    constexpr int64_t  SwapByteOrder(int64_t x) noexcept  { return static_cast<int64_t>(SwapByteOrder(static_cast<uint64_t>(x))); }

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    template <class T> constexpr T NativeToLittleEndian(T x) noexcept { return x; }
    template <class T> constexpr T NativeToBigEndian(T x) noexcept    { return SwapByteOrder(x); }
    template <class T> constexpr T LittleToNativeEndian(T x) noexcept { return x; }
    template <class T> constexpr T BigToNativeEndian(T x) noexcept    { return SwapByteOrder(x); }
#else
    template <class T> constexpr T NativeToLittleEndian(T x) noexcept { return SwapByteOrder(x); }
    template <class T> constexpr T NativeToBigEndian(T x) noexcept    { return x; }
    template <class T> constexpr T LittleToNativeEndian(T x) noexcept { return SwapByteOrder(x); }
    template <class T> constexpr T BigToNativeEndian(T x) noexcept    { return x; }
#endif
    template <class T> constexpr T LittleToBigEndian(T x) noexcept    { return SwapByteOrder(x); }
    template <class T> constexpr T BigToLittleEndian(T x) noexcept    { return SwapByteOrder(x); }
}
