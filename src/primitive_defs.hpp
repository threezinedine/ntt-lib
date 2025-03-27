#pragma once
#include "common.hpp"

#define NTT_TRUE true
#define NTT_FALSE false

namespace NTT_NS
{
#define NTT_PRIMITIVE_TYPE_DEFINITION_FLOAT(fromType, toType, size, min, max, invalid) \
    using toType = fromType;                                                           \
    constexpr toType toType##_invalid = invalid;                                       \
    constexpr toType toType##_min = min;                                               \
    constexpr toType toType##_max = max;                                               \
    static_assert(sizeof(toType) == size, "Invalid size for type " #toType);

#define NTT_PRIMITIVE_TYPE_DEFINITION(fromType, toType, size, min, max) \
    NTT_PRIMITIVE_TYPE_DEFINITION_FLOAT(fromType, toType, size, min, max, ~static_cast<toType>(0))

    NTT_PRIMITIVE_TYPE_DEFINITION(unsigned char, u8, 1, 0, 255);
    NTT_PRIMITIVE_TYPE_DEFINITION(char, i8, 1, -128, 127);
    NTT_PRIMITIVE_TYPE_DEFINITION(unsigned short, u16, 2, 0, 65535);
    NTT_PRIMITIVE_TYPE_DEFINITION(short, i16, 2, -32768, 32767);
    NTT_PRIMITIVE_TYPE_DEFINITION(unsigned int, u32, 4, 0, 4294967295);
    NTT_PRIMITIVE_TYPE_DEFINITION(int, i32, 4, -2147483648, 2147483647);
    NTT_PRIMITIVE_TYPE_DEFINITION(unsigned long long, u64, 8, 0, 0xFFFFFFFFFFFFFFFFULL);
    NTT_PRIMITIVE_TYPE_DEFINITION(long long, i64, 8, 0x8000000000000000LL, 0x7FFFFFFFFFFFFFFFLL);

    NTT_PRIMITIVE_TYPE_DEFINITION_FLOAT(float, f32, 4, -3.402823466e+38f, 3.402823466e+38f, -1.0f);
    NTT_PRIMITIVE_TYPE_DEFINITION_FLOAT(double, f64, 8, -1.7976931348623158e+308, 1.7976931348623158e+308, -1.0);
} // namespace NTT_NS
