#include "gtest/gtest.h"

#include "util/hpta_strings.hpp"

TEST(NumberConverter, to_hex)
{
	ASSERT_TRUE(Hpta_strings::equals_ignorecase("Hello", "hello"));
}
