#pragma once
#include "common.hpp"
#include <string>
#include <vector>

#define NTT_STRING_TRIM_LEFT (1)
#define NTT_STRING_TRIM_RIGHT (1 << 1)

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
         * @return The list of strings which is separated by the delimiters from the current string.
         */
        std::vector<String> split(const String &delimiters = NTT_STRING_SPACE) const;

        /**
         * Delete all space characters from the left or right (or both) side of the current string.
         *
         * @param flags The flags which will be used to determine which side of the current string will be trimmed.
         *      The default value is `NTT_STRING_TRIM_LEFT | NTT_STRING_TRIM_RIGHT`.
         *      Can use only one of the following values: `NTT_STRING_TRIM_LEFT`, `NTT_STRING_TRIM_RIGHT`.
         */
        void trim(u8 flags = NTT_STRING_TRIM_LEFT | NTT_STRING_TRIM_RIGHT);

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
