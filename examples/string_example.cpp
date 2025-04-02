#include <NTTLib.hpp>

using namespace NTT_NS;

int main(void)
{
    std::vector<String> list = String("Hello, World, World!").split(", ");

    print(format("Size of the list: {}", list.size()));

    for (const auto &item : list)
    {
        print(format("{}", item));
    }

    return 0;
}