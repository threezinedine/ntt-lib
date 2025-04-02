#include "string.hpp"
#include "format.hpp"

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

    std::vector<String> String::split(const String &delimiters) const
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

        return splittedStrings;
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