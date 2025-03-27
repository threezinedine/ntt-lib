#pragma once
#include "common.hpp"
#include "string.hpp"

namespace NTT_NS
{

/**
 * Convert a raw format message into the formatted message
 *      which will replace the placeholder "{}" with the value,
 *      the placeholder "{}" can be escaped by using double brackets "{{}}".
 */
#define NTT_FORMAT_TYPE_DECLARE(type) \
    String format(const String &formatMsg, const type &value);

    NTT_FORMAT_TYPE_DECLARE(u8);
    NTT_FORMAT_TYPE_DECLARE(i8);
    NTT_FORMAT_TYPE_DECLARE(u16);
    NTT_FORMAT_TYPE_DECLARE(i16);
    NTT_FORMAT_TYPE_DECLARE(u32);
    NTT_FORMAT_TYPE_DECLARE(i32);
    NTT_FORMAT_TYPE_DECLARE(u64);
    NTT_FORMAT_TYPE_DECLARE(i64);
    NTT_FORMAT_TYPE_DECLARE(f32);
    NTT_FORMAT_TYPE_DECLARE(f64);

    NTT_FORMAT_TYPE_DECLARE(String);
    NTT_FORMAT_TYPE_DECLARE(bool);

    /**
     * Convert a raw format message into the formatted message
     *      which will replace the placeholder "{}" with the value,
     *      the placeholder "{}" can be escaped by using double brackets "{{}}".
     */
    String format(const String &formatMsg, const char *value);

    /**
     * Convert a raw format message into the formatted message
     *      which will replace the placeholder "{}" with the value,
     *      the placeholder "{}" can be escaped by using double brackets "{{}}".
     */
    String format(const String &formatMsg);

    /**
     * Convert a raw format message into the formatted message
     *      which will replace the placeholder "{}" with the value,
     *      the placeholder "{}" can be escaped by using double brackets "{{}}".
     */
    template <typename T, typename... Args>
    String format(const String &formatMsg, const T &value, Args... args)
    {
        return format(format(formatMsg, value), args...);
    }
} // namespace NTT_NS
