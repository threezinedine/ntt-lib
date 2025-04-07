#pragma once
#include "common.hpp"
#include <string>
#include <utility>
#include <vector>

#define NTT_STRING_TRIM_LEFT (1)
#define NTT_STRING_TRIM_RIGHT (1 << 1)
#define NTT_EMPTY_COMPRESS_KEY (std::pair<String, String>{"", ""})

namespace NTT_NS
{
    /**
     * A wrapper class for std::string which will provide more
     *      utility functions in the future for handling strings.
     */
    class String : public std::string
    {
    public:
        String();
        String(const char *str);
        String(const std::string &str);
        String(const String &str);
        String(String &&str);
        ~String();

        String &operator=(const String &str);
        String &operator=(String &&str);

    public:
        // TODO: Add the way for ignoring some pattern inside the string which will not be replaced.
        /**
         * Displace the a string inside the current string into
         *     another string.
         *
         * @param target The string pattern inside the current string which
         *      is needed to be displaced.
         * @param replacement The string which will replace the target string.
         * @param all If `true` the function will replace all the target strings
         *      inside the current string, otherwise it will replace only the first one.
         *      The default value is `false`.
         *
         * @return The new string after displacing the target string with the replacement string.
         */
        String Replace(const String &target, const String &replacement, bool all = NTT_FALSE) const;

        /**
         * Displace the a string inside the current string into
         *     another string. The result will be stored inside the current string.
         *
         * @param target The string pattern inside the current string which
         *      is needed to be displaced.
         * @param replacement The string which will replace the target string.
         * @param all If `true` the function will replace all the target strings
         *      inside the current string, otherwise it will replace only the first one.
         *      The default value is `false`.
         */
        void Replace_I(const String &target, const String &replacement, bool all = NTT_FALSE);

        /**
         * Obtain the list of strings which is separated by the delimiters from
         *      the current string.
         *
         * @param delimiters The delimiters which will be used to split the current string.
         *      If the delimiters is empty, the current string will be returned as a single element.
         *      The default value is `NTT_STRING_SPACE`.
         * @param compress_key The compress key which will be used to compress the strings.
         *      The content inside the compress key will be compressed into a single element which will
         *          not be split by the delimiters.
         *      These keys only work when the compress keys are at the beginning of a splitted element
         *          and at the end of another splitted element.
         *      The default value is `NTT_EMPTY_COMPRESS_KEY`.
         * @return The list of strings which is separated by the delimiters from the current string.
         *
         * @example
         * ```c++
         *      String str = "Hello \"World Mem\" World!";
         *      std::vector<String> list = str.split(" ", {"\"", "\""});
         *      // list[0] = "Hello"
         *      // list[1] = "\"World Mem\"" // The " is at the beginning and end of the separated element.
         *      // list[2] = "World!"
         *
         *      str = String("Hello \"World Mem\"World!");
         *      list = str.split(" ", {"\"", "\""});
         *      // list[0] = "Hello"
         *      // list[1] = "\"World";
         *      // list[2] = "Mem\"World" // The " is not at the end of the separated element.
         * ```
         */
        std::vector<String> split(
            const String &delimiters = NTT_STRING_SPACE,
            const std::pair<String, String> compress_key = NTT_EMPTY_COMPRESS_KEY) const;

        /**
         * Delete all space characters from the left or right (or both) side of the current string.
         *
         * @param flags The flags which will be used to determine which side of the current string will be trimmed.
         *      The default value is `NTT_STRING_TRIM_LEFT | NTT_STRING_TRIM_RIGHT`.
         *      Can use only one of the following values: `NTT_STRING_TRIM_LEFT`, `NTT_STRING_TRIM_RIGHT`.
         */
        void trim(u8 flags = NTT_STRING_TRIM_LEFT | NTT_STRING_TRIM_RIGHT);

        /**
         * Used for checking whether the current string have the similar pattern as given or not.
         *
         * @param pattern The pattern will be used to check. The format of the patern will contains
         *      the `@` for the wildcard string (Ex: "Hello @").
         *
         * @example
         * ```c++
         * bool result = String("Hello World").matchPattern("Hello @"); // result = true
         * bool result = String("HelloWorld").matchPattern("Hello @"); // result = false
         * bool result = String("Hello World").matchPattern("@World"); // result = true
         * bool result = String("Hello World").matchPattern("@@"); // result = true
         * ```
         */
        bool matchPattern(const String &pattern);

        /**
         * Used for checking the current string begins with a given string or not
         *
         * @param pattern The pattern will be used to check.
         * @retval `true` if the current string begins with the given pattern.
         * @retval `false` if the current string is empty or not begins with the given pattern.
         */
        bool startsWith(const String &pattern);

        /**
         * Used for checking the current string ends with a given string or not
         *
         * @param pattern The pattern will be used to check.
         * @retval `true` if the current string ends with the given pattern.
         * @retval `false` if the current string is empty or not ends with the given pattern.
         */
        bool endsWith(const String &pattern);

        /**
         * Join a list of strings into a single string with a delimiter.
         *
         * @param strings The list of strings which will be joined.
         * @param delimiter The delimiter which will be used to join the strings.
         *      The default value is `NTT_STRING_SPACE`.
         * @return The joined string.
         */
        static String Concat(const std::vector<String> &strings, const String &delimiter = NTT_STRING_SPACE);
    };
} // namespace NTT_NS
