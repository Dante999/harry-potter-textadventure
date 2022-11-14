#include <gtest/gtest.h>

#include "hpta-lib/util/hpta_config.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <sstream>

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

TEST(HptaStrings, ends_with)
{
    ASSERT_TRUE(Hpta_strings::ends_with("myfile.json", ".json"));
    ASSERT_TRUE(Hpta_strings::ends_with("myfile.json", "json"));
    ASSERT_FALSE(Hpta_strings::ends_with("myfile.json", ".JSON"));
}

TEST(HptaStrings, get_highlightet_text)
{
    const auto text = "hello *world*. This is *an* example!";

    const auto result = Hpta_strings::get_highlighted_text(text, '*', '*');

    ASSERT_EQ(2, result.size());
    ASSERT_EQ("*world*", result.at(0));
    ASSERT_EQ("*an*", result.at(1));
}

TEST(HptaStrings, replace)
{
    std::string input = "hello there!";
    Hpta_strings::replace(input, "there", "world");

    ASSERT_EQ("hello world!", input);
}

TEST(HptaConfig, read)
{
    std::stringstream ss;

    ss << "key1 = value1\n";
    ss << "key2 = value2\n";
    ss << " key3   =   value3  \n";

    Hpta_config::load(ss);

    ASSERT_EQ("value1", Hpta_config::get_string("key1"));
    ASSERT_EQ("value2", Hpta_config::get_string("key2"));
    ASSERT_EQ("value3", Hpta_config::get_string("key3"));
}
