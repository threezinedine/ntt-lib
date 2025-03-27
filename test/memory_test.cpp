#include "test_common.hpp"

class TestObject
{
public:
    TestObject() = default;
    TestObject(u16 value) : value(value) {}
    u16 value = 0;
};

static NTT_NS::String format(const NTT_NS::String &formatMsg, const TestObject &obj)
{
    return NTT_NS::format(formatMsg, NTT_NS::format("<TestObject value={} />", obj.value));
}

TEST(MemoryTest, CreateScope)
{
    Scope<u16> ptr = CreateScope<u16>(1994);
    EXPECT_EQ(*ptr, 1994);
    EXPECT_EQ(format("{}", ptr), "<Scope value=1994 />");
}

TEST(MemoryTest, CreateShared)
{
    Ref<u16> ptr = CreateRef<u16>(1994);
    EXPECT_EQ(*ptr, 1994);
    EXPECT_EQ(format("{}", ptr), "<Ref value=1994 />");
}

TEST(MemoryTest, ScopeWithCustomedObject)
{
    Scope<TestObject> ptr = CreateScope<TestObject>(1994);
    EXPECT_EQ(ptr->value, 1994);
    EXPECT_EQ(format("{}", ptr), "<Scope value=<TestObject value=1994 /> />");
}