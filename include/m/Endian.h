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

    constexpr uint16_t swapByteOrder(uint16_t x) noexcept { return __builtin_bswap16(x); }
    constexpr int16_t  swapByteOrder(int16_t x) noexcept  { return static_cast<int16_t>(swapByteOrder(static_cast<uint16_t>(x))); }
    constexpr uint32_t swapByteOrder(uint32_t x) noexcept { return __builtin_bswap32(x); }
    constexpr int32_t  swapByteOrder(int32_t x) noexcept  { return static_cast<int32_t>(swapByteOrder(static_cast<uint32_t>(x))); }
    constexpr uint64_t swapByteOrder(uint64_t x) noexcept { return __builtin_bswap64(x); }
    constexpr int64_t  swapByteOrder(int64_t x) noexcept  { return static_cast<int64_t>(swapByteOrder(static_cast<uint64_t>(x))); }

    template <Endian endian, class T> constexpr T nativeToEndian(T x)   { return Endian::native != endian ? swapByteOrder(x) : x; }
    template <Endian endian, class T> constexpr T nativeFromEndian(T x) { return Endian::native != endian ? swapByteOrder(x) : x; }

    template <class T> constexpr T nativeToLittleEndian(T x) noexcept { return nativeToEndian<Endian::little>(x); }
    template <class T> constexpr T nativeToBigEndian(T x) noexcept    { return nativeToEndian<Endian::big>(x); }
    template <class T> constexpr T littleToNativeEndian(T x) noexcept { return nativeFromEndian<Endian::little>(x); }
    template <class T> constexpr T bigToNativeEndian(T x) noexcept    { return nativeFromEndian<Endian::big>(x); }
    template <class T> constexpr T littleToBigEndian(T x) noexcept    { return swapByteOrder(x); }
    template <class T> constexpr T bigToLittleEndian(T x) noexcept    { return swapByteOrder(x); }
}
