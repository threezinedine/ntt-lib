#include "string.hpp"

namespace NTT_NS
{
    String::String() : std::string() {}
    String::String(const char *str) : std::string(str) {}
    String::String(const std::string &str) : std::string(str) {}
    String::String(const String &str) : std::string(str) {}
    String::String(String &&str) : std::string(std::move(str)) {}
    String::~String() {}

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
} // namespace NTT_NS