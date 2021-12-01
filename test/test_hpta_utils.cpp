#include <gtest/gtest.h>

#include "util/hpta_strings.hpp"

TEST(HptaStrings, equals_ignorecase)
{
	ASSERT_TRUE(Hpta_strings::equals_ignorecase("Hello", "hello"));
	ASSERT_TRUE(Hpta_strings::equals_ignorecase("Hello", "Hello"));
	ASSERT_FALSE(Hpta_strings::equals_ignorecase("Hello", "Hi"));
}

TEST(HptaStrings, equals_one_of)
{
	ASSERT_TRUE(Hpta_strings::equals_one_of("Hi", {"Hi", "there"}));
	ASSERT_TRUE(Hpta_strings::equals_one_of("there", {"Hi", "there"}));
	ASSERT_FALSE(Hpta_strings::equals_one_of("Hi", {"Hello", "there"}));
}
