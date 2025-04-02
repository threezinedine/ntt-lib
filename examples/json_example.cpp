#include <NTTLib.hpp>
using namespace NTT_NS;

int main(void)
{
    String jsonString = R"({
        "booleanKey": true,
        "dictkey": {
            "nestedKey1": "nestedValue1",
            "nestedKey2": 456
        },
        "intKey": 1994,
        "listKey": [
            1, 
            2, 
            3
        ],
        "negativeKey": -1994,
        "stringKey": "Hello World"
    })";
    JSON jsonObj = JSON::parse(jsonString);
    print(format("{}", jsonObj.dump()));
    return 0;
}