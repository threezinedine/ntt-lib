#ifdef NTT_PLATFORM_WINDOWS
#include "print.hpp"
#include <Windows.h>
#include <iostream>

namespace NTT_NS
{
    namespace
    {
        WORD getWindowColor(ConsoleColor color)
        {
            switch (color)
            {
            case ConsoleColor::BLACK:
                return 0;
            case ConsoleColor::RED:
                return FOREGROUND_RED;
            case ConsoleColor::GREEN:
                return FOREGROUND_GREEN;
            case ConsoleColor::YELLOW:
                return FOREGROUND_RED | FOREGROUND_GREEN;
            case ConsoleColor::BLUE:
                return FOREGROUND_BLUE;
            case ConsoleColor::MAGENTA:
                return FOREGROUND_RED | FOREGROUND_BLUE;
            case ConsoleColor::CYAN:
                return FOREGROUND_GREEN | FOREGROUND_BLUE;
            case ConsoleColor::WHITE:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            case ConsoleColor::DEFAULT:
            default:
                return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            };
        };
    } // namespace anonymous

    void print(const String &msg, bool newLine, ConsoleColor fgColor, ConsoleColor bgColor)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD attributes = (getWindowColor(fgColor) | getWindowColor(bgColor));
        SetConsoleTextAttribute(hConsole, attributes);
        std::cout << msg;
        if (newLine)
        {
            std::cout << std::endl;
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
} // namespace NTT_NS

#endif