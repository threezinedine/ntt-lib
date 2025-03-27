#pragma once
#include "common.hpp"
#include "color.hpp"
#include "string.hpp"

namespace NTT_NS
{
    /**
     * The os-dependent function to display the text into the console.
     *      The text will be displayed with the specified foreground and background color.
     *      The text will be displayed with the new line character if the newLine is true.
     *
     * @param msg The message to be displayed.
     * @param newLine The flag to display the new line character.
     * @param fgColor The foreground color of the text.
     * @param bgColor The background color of the text.
     */
    void print(const String &msg, bool newLine = true,
               ConsoleColor fgColor = ConsoleColor::DEFAULT,
               ConsoleColor bgColor = ConsoleColor::DEFAULT);
} // namespace NTT_NS
