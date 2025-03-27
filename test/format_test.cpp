#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <NTTLib.hpp>

using namespace NTT_NS;

TEST(FormatTest, CanFormatAllPrimitivetypes)
{
    EXPECT_EQ(format("Hello {}!", 1), "Hello 1!");
    EXPECT_EQ(format("Hello {}!", -232), "Hello -232!");
}

TEST(FormatTest, OnlyDisplay2FloatingPoint)
{
    EXPECT_EQ(format("Hello {}!", 1.23456789f), "Hello 1.23!");
    EXPECT_EQ(format("Hello {}!", 1.23456789), "Hello 1.23!");
}

TEST(FormTest, CanFormatString)
{
    EXPECT_EQ(format("Hello {}!", String("World")), "Hello World!");
    EXPECT_EQ(format("Hello {}!", "World"), "Hello World!");
}

TEST(FormatTest, CanFormatEvenIfTheValueOfSignaturesOrArgsAreNotMatched)
{
    EXPECT_EQ(format("Hello, {}!"), "Hello, {}!");
    EXPECT_EQ(format("Hello, !", 1), "Hello, !");
}

TEST(FormatTest, FormatWithMultipleArgs)
{
    EXPECT_EQ(format("Hello, {}, {}!", 1, "World"), "Hello, 1, World!");
}

TEST(FormatTest, FormatWithBool)
{
    EXPECT_EQ(format("Hello, {}!", NTT_TRUE), "Hello, true!");
    EXPECT_EQ(format("Hello, {}!", NTT_FALSE), "Hello, false!");
}