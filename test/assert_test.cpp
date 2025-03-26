#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <NTTLib.hpp>

TEST(AssertTest, CallNotImplemenationAssertWithoutMessage)
{
#ifdef NTT_DEBUG
    EXPECT_DEATH({ NTT_ASSERT_NOT_IMPLEMENTED; }, ".*");
#else
    NTT_ASSERT_NOT_IMPLEMENTED;
#endif
}

TEST(AssertTest, CallNotImplemenationAssertWithMessage)
{
#ifdef NTT_DEBUG
    EXPECT_DEATH({ NTT_ASSERT_NOT_IMPLEMENTED_M("This is a message"); }, "This is a message");
#else
    NTT_ASSERT_NOT_IMPLEMENTED_M("This is a message");
#endif
}