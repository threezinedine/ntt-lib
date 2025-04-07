#include "format.hpp"
#include <string>
#include <sstream>
#include <iomanip>

namespace NTT_NS
{
#define NTT_FORMAT_TYPE_DEFINITION(type)                       \
    String format(const String &formatMsg, const type &value)  \
    {                                                          \
        return formatMsg.Replace("{}", std::to_string(value)); \
    }

    NTT_FORMAT_TYPE_DEFINITION(u8);
    NTT_FORMAT_TYPE_DEFINITION(i8);
    NTT_FORMAT_TYPE_DEFINITION(u16);
    NTT_FORMAT_TYPE_DEFINITION(i16);
    NTT_FORMAT_TYPE_DEFINITION(u32);
    NTT_FORMAT_TYPE_DEFINITION(i32);
    NTT_FORMAT_TYPE_DEFINITION(u64);
    NTT_FORMAT_TYPE_DEFINITION(i64);

    String format(const String &formatMsg, const f32 &value)
    {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return formatMsg.Replace("{}", stream.str());
    }

    String format(const String &formatMsg, const f64 &value)
    {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;
        return formatMsg.Replace("{}", stream.str());
    }

    String format(const String &formatMsg, const String &value)
    {
        return formatMsg.Replace("{}", value);
    }

    String format(const String &formatMsg, const char *value)
    {
        return formatMsg.Replace("{}", value);
    }

    String format(const String &formatMsg)
    {
        return formatMsg;
    }

    String format(const String &formatMsg, const bool &value)
    {
        return formatMsg.Replace("{}", value ? "true" : "false");
    }

#define NTT_FORMAT_TYPE_VECTOR_DEFINITION(type)                                 \
    String format(const String &formatMsg, const std::vector<type> &value)      \
    {                                                                           \
        String result = formatMsg;                                              \
        std::vector<String> elementStrings;                                     \
        for (const auto &item : value)                                          \
        {                                                                       \
            elementStrings.push_back(format("{}", item));                       \
        }                                                                       \
                                                                                \
        String arrayStr = format("[{}]", String::Concat(elementStrings, ", ")); \
        return format(formatMsg, arrayStr);                                     \
    }

    NTT_FORMAT_TYPE_VECTOR_DEFINITION(u8);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(i8);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(u16);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(i16);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(u32);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(i32);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(u64);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(i64);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(f32);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(f64);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(String);
    NTT_FORMAT_TYPE_VECTOR_DEFINITION(bool);
} // namespace NTT_NS