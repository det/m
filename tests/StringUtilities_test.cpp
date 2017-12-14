#include "m/StringUtilities.h"
#include "gtest/gtest.h"

TEST(StringUtilities, levenshteinDistance) {
	EXPECT_EQ(m::levenshteinDistance("the quick brown fox", "he qquick brown foxx"), 3);
}
