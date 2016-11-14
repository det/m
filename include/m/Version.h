#pragma once
#include <string>
#include <cstdio>
#include <cinttypes>

namespace m {
    struct Version {
        uint8_t  major    = 0;
        uint8_t  minor    = 0;
        uint16_t revision = 0;
        uint32_t build    = 0;

        static constexpr Version fromInt64(uint64_t i) noexcept;
        static Version           fromString(const char* s) noexcept;

        constexpr uint64_t       toInt64() const noexcept;
        std::string              toString() const;
        std::string              toShortString() const; // without trailing zeroes after major.minor

        constexpr bool operator==(const Version& other) const noexcept { return toInt64() == other.toInt64(); }
        constexpr bool operator!=(const Version& other) const noexcept { return toInt64() != other.toInt64(); }
        constexpr bool operator< (const Version& other) const noexcept { return toInt64() <  other.toInt64(); }
        constexpr bool operator> (const Version& other) const noexcept { return toInt64() >  other.toInt64(); }
        constexpr bool operator<=(const Version& other) const noexcept { return toInt64() <= other.toInt64(); }
        constexpr bool operator>=(const Version& other) const noexcept { return toInt64() >= other.toInt64(); }
    };

    constexpr Version Version::fromInt64(uint64_t i) noexcept {
        return { uint8_t((i >>  56) & 0x00000000000000ff),
                 uint8_t((i >>  48) & 0x00000000000000ff),
                 uint16_t((i >> 32) & 0x000000000000ffff),
                 uint32_t((i >>  0) & 0x00000000ffffffff)
        };
    }

    inline Version Version::fromString(const char* s) noexcept {
        Version v;
        std::sscanf(s, "%" SCNu8 ".%" SCNu8 ".%" SCNu16 ".%" SCNu32,
                   &v.major,
                   &v.minor,
                   &v.revision,
                   &v.build);
        return v;
    }

    constexpr uint64_t Version::toInt64() const noexcept {
        return (uint64_t{major}    << 56) +
               (uint64_t{minor}    << 48) +
               (uint64_t{revision} << 32) +
               build;
    }

    inline std::string Version::toString() const {
        return std::to_string(major)    + '.' +
               std::to_string(minor)    + '.' +
               std::to_string(revision) + '.' +
               std::to_string(build);
    }

    inline std::string Version::toShortString() const {
        if (build)    { return toString(); }
        if (revision) { return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(revision); }
        return std::to_string(major) + '.' + std::to_string(minor);
    }
}
