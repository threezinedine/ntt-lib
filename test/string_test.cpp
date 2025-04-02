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

TEST(StringTest, TestSplitStringWithDelimiters)
{
    String str = "Hello, World, World!";
    std::vector<String> list = str.split(", ");
    EXPECT_EQ(list.size(), 3);
    EXPECT_THAT(list, ::testing::ElementsAre("Hello", "World", "World!"));
}

TEST(StringTest, SplitStringWithEmptyString)
{
    String str = "Testing split with empty string";
    std::vector<String> list = str.split("");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "Testing split with empty string");
}

TEST(StringTest, SplitWithNonExistedDelimiters)
{
    String str = "Hello, World, World!";
    std::vector<String> list = str.split("NTT");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "Hello, World, World!");
}

TEST(StringTest, SplitEmptyString)
{
    String str = "";
    std::vector<String> list = str.split(" ");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "");
}

TEST(StringTest, SplitWithDelimeterAtTheEnd)
{
    String str = "Hello! World, ";
    std::vector<String> list = str.split(", ");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "Hello! World");
    EXPECT_EQ(list[1], "");
}

TEST(StringTest, SplitWithDelimeterAtTheBeginning)
{
    String str = ", Hello1 World";
    std::vector<String> list = str.split(", ");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "");
    EXPECT_EQ(list[1], "Hello1 World");
}

TEST(StringTest, SplitStringWithMultipleDelimiters)
{
    String str = "Hello, World, World!";
    std::vector<String> list = str.split(", ");
    EXPECT_EQ(list.size(), 3);
}
