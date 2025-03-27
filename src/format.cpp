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
} // namespace NTT_NS