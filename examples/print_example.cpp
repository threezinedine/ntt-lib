#include <NTTLib.hpp>
using namespace NTT_NS;

int main(void)
{
    print("Hello, World!");
    print("Hello, World!", false, ConsoleColor::RED, ConsoleColor::BLUE);
    print("Hello, World!", true, ConsoleColor::GREEN, ConsoleColor::YELLOW);
    print("Hello, World!");
    return 0;
}