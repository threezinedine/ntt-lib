#include "test_common.hpp"

TEST(StringTest, TestReplace_Normal)
{
    EXPECT_EQ(String("Hello, World, World!").Replace("World", "NTT"), "Hello, NTT, World!");
}

TEST(StringTest, TestReplace_All)
{
    EXPECT_EQ(String("Hello, World, World!").Replace("World", "NTT", NTT_TRUE), "Hello, NTT, NTT!");
}

TEST(StringTest, TestInternalReplace_Normal)
{
    String str = "Hello, World, World!";
    str.Replace_I("World", "NTT");
    EXPECT_EQ(str, "Hello, NTT, World!");
}

TEST(StringTest, TestInternalReplace_All)
{
    String str = "Hello, World, World!";
    str.Replace_I("World", "NTT", NTT_TRUE);
    EXPECT_EQ(str, "Hello, NTT, NTT!");
}