#pragma once
#include "common.hpp"
#include <string>

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
    };
} // namespace NTT_NS
