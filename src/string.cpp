#include "string.hpp"
#include "format.hpp"
#include "def_utils.hpp"
#include <cstring>

#define PATTERN_TRIGGER "@"

namespace NTT_NS
{
    String::String() : std::string() {}
    String::String(const char *str) : std::string(str) {}
    String::String(const std::string &str) : std::string(str) {}
    String::String(const String &str) : std::string(str) {}
    String::String(String &&str) : std::string(std::move(str)) {}
    String::~String() {}

    String &String::operator=(const String &str)
    {
        std::string::operator=(str);
        return *this;
    }

    String &String::operator=(String &&str)
    {
        std::string::operator=(std::move(str));
        return *this;
    }

    String String::Replace(const String &target, const String &replacement, bool all) const
    {
        String result = *this;
        size_t pos = 0;
        while ((pos = result.find(target, pos)) != std::string::npos)
        {
            result.replace(pos, target.length(), replacement);
            pos += replacement.length();
            if (!all)
            {
                break;
            }
        }
        return result;
    }

    void String::Replace_I(const String &target, const String &replacement, bool all)
    {
        String result = Replace(target, replacement, all);
        this->swap(result);
    }

    std::vector<String> String::split(
        const String &delimiters,
        const std::pair<String, String> compress_key) const
    {
        std::vector<String> splittedStrings;
        if (delimiters == NTT_STRING_EMPTY)
        {
            splittedStrings.push_back(*this);
            return splittedStrings;
        }

        size_t startPos = 0;

        size_t currentDelimiterPos = find(delimiters, startPos);

        while (currentDelimiterPos != std::string::npos)
        {
            String current = substr(startPos, currentDelimiterPos - startPos);
            splittedStrings.push_back(current);

            startPos = currentDelimiterPos + delimiters.length();
            currentDelimiterPos = find(delimiters, startPos);
        }

        String last = substr(startPos);
        splittedStrings.push_back(last);

        // Compress the strings
        if (compress_key.first == NTT_STRING_EMPTY)
        {
            return splittedStrings;
        }

        std::vector<String> newSplittedStrings;

        bool isCompressKeyFound = false;
        u32 compressKeyIndex = 0;

        for (u32 tempStringIndex = 0; tempStringIndex < (u32)splittedStrings.size(); tempStringIndex++)
        {
            String &tempString = splittedStrings[tempStringIndex];

            if (tempString.startsWith(compress_key.first) && !isCompressKeyFound)
            {
                isCompressKeyFound = true;
                compressKeyIndex = tempStringIndex;
                continue;
            }

            if (isCompressKeyFound)
            {
                if (tempString.endsWith(compress_key.second))
                {
                    String newCompressedString = "";
                    for (u32 i = compressKeyIndex; i <= tempStringIndex; i++)
                    {
                        newCompressedString += splittedStrings[i];
                        if (i < tempStringIndex)
                        {
                            newCompressedString += delimiters;
                        }
                    }
                    newSplittedStrings.push_back(newCompressedString);
                    isCompressKeyFound = false;
                }

                continue;
            }

            newSplittedStrings.push_back(tempString);
        }

        if (isCompressKeyFound)
        {
            for (u32 i = compressKeyIndex; i < splittedStrings.size(); i++)
            {
                newSplittedStrings.push_back(splittedStrings[i]);
            }
        }

        return newSplittedStrings;
    }

    bool String::matchPattern(const String &pattern)
    {
        const String patternTrigger = PATTERN_TRIGGER;
        if (pattern.length() > length())
        {
            return false;
        }

        size_t currentPatternIndex = 0;
        size_t previousPatternIndex = 0;

        size_t currentStringIndex = 0;

        while (currentPatternIndex != std::string::npos)
        {
            size_t currentPatternStringLength = currentPatternIndex - previousPatternIndex;
            const String currentPatternString = pattern.substr(previousPatternIndex, currentPatternStringLength);

            size_t matchedPatternInStringIndex = find(currentPatternString, currentStringIndex);

            if (matchedPatternInStringIndex == std::string::npos)
            {
                return false;
            }

            currentStringIndex += matchedPatternInStringIndex + currentPatternStringLength;
            previousPatternIndex = currentPatternIndex + patternTrigger.length();
            currentPatternIndex = pattern.find(patternTrigger, previousPatternIndex);
        }

        size_t currentPatternStringLength = pattern.length() - previousPatternIndex;
        const String currentPatternString = pattern.substr(previousPatternIndex, currentPatternStringLength);
        const String tempSubString = substr(length() - currentPatternStringLength, currentPatternStringLength);

        if (tempSubString != currentPatternString)
        {
            return false;
        }

        return true;
    }

    void String::trim(u8 flags)
    {
        if (length() == 0)
        {
            return;
        }

        if (flags & NTT_STRING_TRIM_LEFT)
        {
            while (isspace(at(0)))
            {
                erase(0, 1);

                if (length() == 0)
                {
                    break;
                }
            }
        }

        if (length() == 0)
        {
            return;
        }

        if (flags & NTT_STRING_TRIM_RIGHT)
        {
            while (isspace(at(length() - 1)))
            {
                erase(length() - 1, 1);

                if (length() == 0)
                {
                    break;
                }
            }
        }
    }

    bool String::startsWith(const String &pattern)
    {
        if (pattern.length() > length())
        {
            return false;
        }

        return substr(0, pattern.length()) == pattern;
    }

    bool String::endsWith(const String &pattern)
    {
        if (pattern.length() > length())
        {
            return false;
        }

        return substr(length() - pattern.length()) == pattern;
    }

    String String::Concat(const std::vector<String> &strings, const String &delimiter)
    {
        if (strings.size() == 0)
        {
            return NTT_STRING_EMPTY;
        }

        String result = strings[0];
        for (size_t i = 1; i < strings.size(); i++)
        {
            result = format("{}{}{}", result, delimiter, strings[i]);
        }

        return result;
    }
} // namespace NTT_NS