#include <NTTLib.hpp>

using namespace NTT_NS;

int main(void)
{
    std::vector<String> list = String("Hello, World, World!").split(", ");
    print(format("List: {}", list));
    print(format("Compress List: {}", String("Hello \"World Mem\" World")
                                          .split(" ", {"\"", "\""})));
    return 0;
}