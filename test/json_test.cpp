#include "test_common.hpp"

class JSONTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        obj = JSON::parse(jsonString);
    }

    void TearDown() override
    {
    }

    JSON obj;

    String jsonString = R"({
        "booleanKey": true,
        "dictkey": {
            "nestedKey1": "nestedValue1",
            "nestedKey2": 456
        },
        "u32Key": 1994,
        "floatKey": 1994.123,
        "doubleKey": 1994.123456789,
        "u8Key": 255,
        "i8Key": -64,
        "u16Key": 60335,
        "i16Key": -30768,
        "listKey": [
            1, 
            2, 
            3
        ],
        "listOfObjects": [
            {
                "nestedKey1": "nestedValue1",
                "nestedKey2": 456
            },
            {
                "nestedKey1": "nestedValue2",
                "nestedKey2": 789
            }
        ],
        "listOfMixedTypes": [
            true,
            false
        ],
        "i32Key": -1994,
        "stringKey": "Hello World"
    })";
};

TEST_F(JSONTest, ParseAValidJSONAndDumpIt)
{
    JSON jsonObj = JSON::parse(jsonString);
    String dumpedString = jsonObj.dump();

    EXPECT_THAT(jsonObj.keys(),
                ::testing::Contains("booleanKey"));
    EXPECT_THAT(jsonObj.keys(),
                ::testing::Contains("dictkey"));
    EXPECT_THAT(jsonObj.keys(),
                ::testing::Contains("u32Key"));
    EXPECT_THAT(jsonObj.keys(),
                ::testing::Contains("u8Key"));
    EXPECT_THAT(jsonObj.keys(),
                ::testing::Contains("i8Key"));
}

TEST_F(JSONTest, IsTypeTestingReturnsTrue)
{
    EXPECT_TRUE(obj.isType<bool>("booleanKey"));
    EXPECT_TRUE(obj.isType<u32>("u32Key"));
    EXPECT_TRUE(obj.isType<u8>("u8Key"));
    EXPECT_TRUE(obj.isType<i8>("i8Key"));
    EXPECT_TRUE(obj.isType<u16>("u16Key"));
    EXPECT_TRUE(obj.isType<i16>("i16Key"));
    EXPECT_TRUE(obj.isType<String>("stringKey"));
    EXPECT_TRUE(obj.isType<JSON>("dictkey"));

    EXPECT_TRUE(obj.isType<u32>("u32Key"));
    EXPECT_TRUE(obj.isType<u32>("u8Key"));
    EXPECT_TRUE(obj.isType<u32>("u16Key"));

    EXPECT_TRUE(obj.isType<i32>("u16Key"));
    EXPECT_TRUE(obj.isType<i32>("i16Key"));
    EXPECT_TRUE(obj.isType<i32>("i8Key"));

    EXPECT_TRUE(obj.isType<i16>("u8Key"));
    EXPECT_TRUE(obj.isType<i16>("i8Key"));
    EXPECT_TRUE(obj.isType<i16>("i16Key"));
}

TEST_F(JSONTest, IsTypeTestingReturnsFalse)
{
    EXPECT_FALSE(obj.isType<bool>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<u32>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<u8>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<i8>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<u16>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<i16>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<String>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<JSON>("nonExistentKey"));

    EXPECT_FALSE(obj.isType<bool>("u32Key"));
    EXPECT_FALSE(obj.isType<u8>("i8Key"));
    EXPECT_FALSE(obj.isType<u16>("i16Key"));
    EXPECT_FALSE(obj.isType<u32>("i32Key"));
}

TEST_F(JSONTest, IsTypeSelf)
{
    EXPECT_FALSE(obj.isType<JSON>("nonExistentKey"));
    EXPECT_FALSE(obj.isType<JSON>("u32Key"));
    EXPECT_FALSE(obj.isType<JSON>("i32Key"));
    EXPECT_FALSE(obj.isType<JSON>("u8Key"));
    EXPECT_FALSE(obj.isType<JSON>("i8Key"));
    EXPECT_FALSE(obj.isType<JSON>("u16Key"));
    EXPECT_FALSE(obj.isType<JSON>("i16Key"));
    EXPECT_FALSE(obj.isType<JSON>("stringKey"));
}

TEST_F(JSONTest, IsTypeList)
{
    EXPECT_TRUE(obj.isList("listKey"));
    EXPECT_FALSE(obj.isList("nonExistentKey"));
    EXPECT_FALSE(obj.isList("u32Key"));
    EXPECT_FALSE(obj.isList("i32Key"));
    EXPECT_FALSE(obj.isList("u8Key"));
    EXPECT_FALSE(obj.isList("i8Key"));
    EXPECT_FALSE(obj.isList("u16Key"));
}

TEST_F(JSONTest, ParseInvalidJSONString)
{
    String invalidJsonString = R"({"key": "value",)";
    EXPECT_THROW(JSON::parse(invalidJsonString), std::runtime_error);
}

TEST_F(JSONTest, GetBooleanTesting)
{
    EXPECT_TRUE(obj.get<bool>("booleanKey", false));
    EXPECT_FALSE(obj.get<bool>("nonExistentKey", false));
    EXPECT_FALSE(obj.get<bool>("u32Key", false));
    EXPECT_FALSE(obj.get<bool>("stringKey", false));
    EXPECT_FALSE(obj.get<bool>("u8Key", false));
    EXPECT_FALSE(obj.get<bool>("i8Key", false));
    EXPECT_FALSE(obj.get<bool>("u16Key", false));
    EXPECT_FALSE(obj.get<bool>("i16Key", false));
    EXPECT_FALSE(obj.get<bool>("floatKey", false));
    EXPECT_FALSE(obj.get<bool>("doubleKey", false));
}

TEST_F(JSONTest, GetU32Testing)
{
    EXPECT_EQ(obj.get<u32>("u32Key", 0), 1994);
    EXPECT_EQ(obj.get<u32>("u8Key", 0), 255);
    EXPECT_EQ(obj.get<u32>("i8Key", 0), 0);
    EXPECT_EQ(obj.get<u32>("u16Key", 0), 60335);
    EXPECT_EQ(obj.get<u32>("i16Key", 0), 0);
    EXPECT_EQ(obj.get<u32>("i32Key", 0), 0);
    EXPECT_EQ(obj.get<u32>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<u32>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<u32>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<u32>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<u32>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetI32Testing)
{
    EXPECT_EQ(obj.get<i32>("u32Key", 0), 1994);
    EXPECT_EQ(obj.get<i32>("i32Key", 0), -1994);
    EXPECT_EQ(obj.get<i32>("u8Key", 0), 255);
    EXPECT_EQ(obj.get<i32>("i8Key", 0), -64);
    EXPECT_EQ(obj.get<i32>("u16Key", 0), 60335);
    EXPECT_EQ(obj.get<i32>("i16Key", 0), -30768);
    EXPECT_EQ(obj.get<i32>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<i32>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<i32>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<i32>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<i32>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetU8Testing)
{
    EXPECT_EQ(obj.get<u8>("u32Key", 0), 0);
    EXPECT_EQ(obj.get<u8>("u8Key", 0), 255);
    EXPECT_EQ(obj.get<u8>("i32Key", 0), 0);
    EXPECT_EQ(obj.get<u8>("i32Key", 0), 0);
    EXPECT_EQ(obj.get<u8>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<u8>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<u8>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<u8>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<u8>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetI8Testing)
{
    EXPECT_EQ(obj.get<i8>("u32Key", 0), 0);
    EXPECT_EQ(obj.get<i8>("u8Key", 0), 0);
    EXPECT_EQ(obj.get<i8>("i8Key", 0), -64);
    EXPECT_EQ(obj.get<i8>("i32Key", 0), 0);
    EXPECT_EQ(obj.get<i8>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<i8>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<i8>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<i8>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<i8>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetU16STesting)
{
    EXPECT_EQ(obj.get<u16>("u32Key", 0), 1994);
    EXPECT_EQ(obj.get<u16>("u8Key", 0), 255);
    EXPECT_EQ(obj.get<u16>("i8Key", 0), 0);
    EXPECT_EQ(obj.get<u16>("u16Key", 0), 60335);
    EXPECT_EQ(obj.get<u16>("i16Key", 0), 0);
    EXPECT_EQ(obj.get<u16>("i32Key", 0), 0);
    EXPECT_EQ(obj.get<u16>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<u16>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<u16>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<u16>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<u16>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetI16Testing)
{
    EXPECT_EQ(obj.get<i16>("u32Key", 0), 1994);
    EXPECT_EQ(obj.get<i16>("u8Key", 0), 255);
    EXPECT_EQ(obj.get<i16>("i8Key", 0), -64);
    EXPECT_EQ(obj.get<i16>("u16Key", 0), 0);
    EXPECT_EQ(obj.get<i16>("i16Key", 0), -30768);
    EXPECT_EQ(obj.get<i16>("i32Key", 0), -1994);
    EXPECT_EQ(obj.get<i16>("nonExistentKey", 0), 0);
    EXPECT_EQ(obj.get<i16>("stringKey", 0), 0);
    EXPECT_EQ(obj.get<i16>("booleanKey", 0), 0);
    EXPECT_EQ(obj.get<i16>("floatKey", 0), 0);
    EXPECT_EQ(obj.get<i16>("doubleKey", 0), 0);
}

TEST_F(JSONTest, GetStringTesting)
{
    EXPECT_EQ(obj.get<String>("stringKey", ""), "Hello World");
    EXPECT_EQ(obj.get<String>("nonExistentKey", ""), "");
    EXPECT_EQ(obj.get<String>("u32Key", ""), "");
    EXPECT_EQ(obj.get<String>("booleanKey", ""), "");
    EXPECT_EQ(obj.get<String>("u8Key", ""), "");
    EXPECT_EQ(obj.get<String>("i8Key", ""), "");
    EXPECT_EQ(obj.get<String>("u16Key", ""), "");
    EXPECT_EQ(obj.get<String>("i16Key", ""), "");
    EXPECT_EQ(obj.get<String>("i32Key", ""), "");
}

TEST_F(JSONTest, GetAnotherJSONObject)
{
    JSON anotherObj = obj.get<JSON>("dictkey", JSON());
    EXPECT_EQ(anotherObj.get<String>("nestedKey1", ""), "nestedValue1");
    EXPECT_EQ(anotherObj.get<u32>("nestedKey2", 0), 456);
}

TEST_F(JSONTest, GetAnotherJSONObjectWithInvalidKeyType)
{
    EXPECT_THAT(obj.get<JSON>("nonExistentKey", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("u32Key", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("u8Key", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("i8Key", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("u16Key", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("i16Key", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("stringKey", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("booleanKey", JSON()).keys(), ::testing::IsEmpty());
    EXPECT_THAT(obj.get<JSON>("listKey", JSON()).keys(), ::testing::IsEmpty());
}

TEST_F(JSONTest, GetFloatTesting)
{
    EXPECT_THAT(obj.get<f32>("floatKey", 0), ::testing::FloatEq(1994.123));
    EXPECT_THAT(obj.get<f64>("doubleKey", 0), ::testing::DoubleEq(1994.123456789));

    EXPECT_THAT(obj.get<f32>("nonExistentKey", 0), 0);
    EXPECT_THAT(obj.get<f64>("nonExistentKey", 0), 0);

    EXPECT_THAT(obj.get<f32>("doubleKey", 0), ::testing::FloatEq(1994.123456789));
    EXPECT_THAT(obj.get<f64>("floatKey", 0), ::testing::DoubleEq(1994.123));

    EXPECT_THAT(obj.get<f32>("u32Key", 0), ::testing::FloatEq(1994));
    EXPECT_THAT(obj.get<f64>("u32Key", 0), ::testing::DoubleEq(1994));

    EXPECT_THAT(obj.get<f32>("i32Key", 0), ::testing::FloatEq(-1994));
    EXPECT_THAT(obj.get<f64>("i32Key", 0), ::testing::DoubleEq(-1994));

    EXPECT_THAT(obj.get<f32>("u8Key", 0), ::testing::FloatEq(255));
    EXPECT_THAT(obj.get<f64>("u8Key", 0), ::testing::DoubleEq(255));

    EXPECT_THAT(obj.get<f32>("i8Key", 0), ::testing::FloatEq(-64));
    EXPECT_THAT(obj.get<f64>("i8Key", 0), ::testing::DoubleEq(-64));

    EXPECT_THAT(obj.get<f32>("u16Key", 0), ::testing::FloatEq(60335));
    EXPECT_THAT(obj.get<f64>("u16Key", 0), ::testing::DoubleEq(60335));

    EXPECT_THAT(obj.get<f32>("i16Key", 0), ::testing::FloatEq(-30768));
    EXPECT_THAT(obj.get<f64>("i16Key", 0), ::testing::DoubleEq(-30768));
}

TEST_F(JSONTest, GetListTesting)
{
    ASSERT_NO_THROW(obj.getList<u32>("listKey"));
    EXPECT_THAT(obj.getList<u32>("listKey"), ::testing::ElementsAre(1, 2, 3));
}

TEST_F(JSONTest, GetListOfObjectsTesting)
{
    ASSERT_NO_THROW(obj.getList<JSON>("listOfObjects"));
    std::vector<JSON> listOfObjects = obj.getList<JSON>("listOfObjects");
    EXPECT_EQ(listOfObjects.size(), 2);
    EXPECT_EQ(listOfObjects[0].get<String>("nestedKey1", ""), "nestedValue1");
    EXPECT_EQ(listOfObjects[0].get<u32>("nestedKey2", 0), 456);
    EXPECT_EQ(listOfObjects[1].get<String>("nestedKey1", ""), "nestedValue2");
    EXPECT_EQ(listOfObjects[1].get<u32>("nestedKey2", 0), 789);
}

TEST_F(JSONTest, GetListOfMixedTypesTesting)
{
    ASSERT_NO_THROW(obj.getList<bool>("listOfMixedTypes"));
    std::vector<bool> listOfMixedTypes = obj.getList<bool>("listOfMixedTypes");
    EXPECT_EQ(listOfMixedTypes.size(), 2);
    EXPECT_EQ(listOfMixedTypes[0], true);
    EXPECT_EQ(listOfMixedTypes[1], false);
}
