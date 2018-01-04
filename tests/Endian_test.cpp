#include "m/Endian.h"
#include "gtest/gtest.h"

TEST(Endian, basic) {
    static_assert(m::swapByteOrder(uint16_t{0x0011}) == 0x1100);
    static_assert(m::swapByteOrder(int16_t{0x0011}) == 0x1100);
    static_assert(m::swapByteOrder(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::swapByteOrder(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::swapByteOrder(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::swapByteOrder(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

    static_assert(m::nativeToEndian<m::Endian::big>(uint16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToEndian<m::Endian::big>(int16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToEndian<m::Endian::big>(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::nativeToEndian<m::Endian::big>(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::nativeToEndian<m::Endian::big>(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::nativeToEndian<m::Endian::big>(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::nativeToEndian<m::Endian::little>(uint16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToEndian<m::Endian::little>(int16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToEndian<m::Endian::little>(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::nativeToEndian<m::Endian::little>(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::nativeToEndian<m::Endian::little>(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::nativeToEndian<m::Endian::little>(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

    static_assert(m::nativeToLittleEndian(uint16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToLittleEndian(int16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToLittleEndian(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::nativeToLittleEndian(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::nativeToLittleEndian(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::nativeToLittleEndian(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

    static_assert(m::nativeToBigEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToBigEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToBigEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::nativeToBigEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::nativeToBigEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::nativeToBigEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::littleToNativeEndian(uint16_t{0x0011}) == 0x0011);
    static_assert(m::littleToNativeEndian(int16_t{0x0011}) == 0x0011);
    static_assert(m::littleToNativeEndian(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::littleToNativeEndian(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::littleToNativeEndian(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::littleToNativeEndian(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

    static_assert(m::bigToNativeEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::bigToNativeEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::bigToNativeEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::bigToNativeEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::bigToNativeEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::bigToNativeEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

#else

    static_assert(m::nativeToEndian<m::Endian::big>(uint16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToEndian<m::Endian::big>(int16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToEndian<m::Endian::big>(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::nativeToEndian<m::Endian::big>(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::nativeToEndian<m::Endian::big>(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::nativeToEndian<m::Endian::big>(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

    static_assert(m::nativeToEndian<m::Endian::little>(uint16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToEndian<m::Endian::little>(int16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToEndian<m::Endian::little>(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::nativeToEndian<m::Endian::little>(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::nativeToEndian<m::Endian::little>(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::nativeToEndian<m::Endian::little>(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::nativeToLittleEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToLittleEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::nativeToLittleEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::nativeToLittleEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::nativeToLittleEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::nativeToLittleEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::nativeToBigEndian(uint16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToBigEndian(int16_t{0x0011}) == 0x0011);
    static_assert(m::nativeToBigEndian(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::nativeToBigEndian(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::nativeToBigEndian(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::nativeToBigEndian(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

    static_assert(m::littleToNativeEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::littleToNativeEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::littleToNativeEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::littleToNativeEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::littleToNativeEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::littleToNativeEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::bigToNativeEndian(uint16_t{0x0011}) == 0x0011);
    static_assert(m::bigToNativeEndian(int16_t{0x0011}) == 0x0011);
    static_assert(m::bigToNativeEndian(uint32_t{0x00112233}) == uint32_t{0x00112233});
    static_assert(m::bigToNativeEndian(int32_t{0x00112233}) == int32_t{0x00112233});
    static_assert(m::bigToNativeEndian(uint64_t{0x0011223344556677}) == uint64_t{0x0011223344556677});
    static_assert(m::bigToNativeEndian(int64_t{0x0011223344556677}) == int64_t{0x0011223344556677});

#endif

    static_assert(m::littleToBigEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::littleToBigEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::littleToBigEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::littleToBigEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::littleToBigEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::littleToBigEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});

    static_assert(m::bigToLittleEndian(uint16_t{0x0011}) == 0x1100);
    static_assert(m::bigToLittleEndian(int16_t{0x0011}) == 0x1100);
    static_assert(m::bigToLittleEndian(uint32_t{0x00112233}) == uint32_t{0x33221100});
    static_assert(m::bigToLittleEndian(int32_t{0x00112233}) == int32_t{0x33221100});
    static_assert(m::bigToLittleEndian(uint64_t{0x0011223344556677}) == uint64_t{0x7766554433221100});
    static_assert(m::bigToLittleEndian(int64_t{0x0011223344556677}) == int64_t{0x7766554433221100});
}
