#include "m/Math.h"
#include "gtest/gtest.h"
#include <cmath>
#include <cstdint>
#include <limits>

TEST(Math, basic) {
    EXPECT_FALSE(m::ispow2(0u));
    EXPECT_TRUE(m::ispow2(1u));
    EXPECT_TRUE(m::ispow2(2u));
    EXPECT_TRUE(m::ispow2(4u));
    EXPECT_FALSE(m::ispow2(7u));
    EXPECT_FALSE(m::ispow2(122u));
    EXPECT_FALSE(m::ispow2(std::numeric_limits<uint32_t>::max()));
    EXPECT_TRUE(m::ispow2(uint64_t{std::numeric_limits<uint32_t>::max()} + 1));
}
