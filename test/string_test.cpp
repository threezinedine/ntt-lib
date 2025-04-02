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

TEST(StringTest, TestTrimDefault)
{
    String str = " Hello, World! ";
    str.trim();
    EXPECT_EQ(str, "Hello, World!");
}

TEST(StringTest, TestTrimLeft)
{
    String str = " Hello, World! ";
    str.trim(NTT_STRING_TRIM_LEFT);
    EXPECT_EQ(str, "Hello, World! ");
}

TEST(StringTest, TestTrimRight)
{
    String str = " Hello, World! ";
    str.trim(NTT_STRING_TRIM_RIGHT);
    EXPECT_EQ(str, " Hello, World!");
}

TEST(StringTest, TestTrimWithNoSpace)
{
    String str = "Hello, World!";
    str.trim();
    EXPECT_EQ(str, "Hello, World!");
}

TEST(StringTest, TestTrimWithEmptyFlags)
{
    String str = " Hello, World! ";
    str.trim(0);
    EXPECT_EQ(str, " Hello, World! ");
}

TEST(StringTest, TestTrimEmtpyString)
{
    String str = "";
    str.trim();
    EXPECT_EQ(str, "");
}

TEST(StringTest, TestTrimAListOfSpaceCharactersWithFullFlags)
{
    String str = "                                   ";
    str.trim();
    EXPECT_EQ(str, "");
}

TEST(StringTest, TestTrimRightOfEmtpyString)
{
    String str = "";
    str.trim(NTT_STRING_TRIM_RIGHT);
    EXPECT_EQ(str, "");
}

TEST(StringTest, TestTrimLeftOfEmtpyString)
{
    String str = "";
    str.trim(NTT_STRING_TRIM_LEFT);
    EXPECT_EQ(str, "");
}

TEST(StringTest, JoinStrings)
{
    std::vector<String> strings = {"Hello", "World", "!"};
    String delimiter = ", ";
    String result = String::Concat(strings, delimiter);
    EXPECT_EQ(result, "Hello, World, !");
}

TEST(StringTest, JoinStringsWithEmptyString)
{
    std::vector<String> strings = {"Hello", "", "World", "!"};
    String delimiter = ", ";
    String result = String::Concat(strings, delimiter);
    EXPECT_EQ(result, "Hello, , World, !");
}

TEST(StringTest, JoinStringsWithEmptyDelimiter)
{
    std::vector<String> strings = {"Hello", "World", "!"};
    String delimiter = "";
    String result = String::Concat(strings, delimiter);
    EXPECT_EQ(result, "HelloWorld!");
}

TEST(StringTest, JoinStringsWithEmptyStringList)
{
    std::vector<String> strings = {};
    String delimiter = ", ";
    String result = String::Concat(strings, delimiter);
    EXPECT_EQ(result, "");
}