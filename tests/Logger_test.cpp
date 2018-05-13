#include "m/Logger.h"
#include "gtest/gtest.h"

TEST(Logger, basic) {
    M_LOG_DEBUG("{} is only a {}", "This", "test.");
}
