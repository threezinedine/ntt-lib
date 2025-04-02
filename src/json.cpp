#include "json.hpp"
#include "nlohmann/json.hpp"

namespace NTT_NS
{
    namespace internal
    {
        template <typename T>
        bool isType(const nlohmann::json &jsonObj);

        template <>
        bool isType<bool>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_boolean();
        }

        template <>
        bool isType<u32>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_number_unsigned();
        }

        template <>
        bool isType<i32>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_number_integer();
        }

        template <>
        bool isType<u8>(const nlohmann::json &jsonObj)
        {
            if (!jsonObj.is_number_unsigned())
            {
                return false;
            }

            u32 value = jsonObj.get<u32>();

            if (value > u8_max || value < u8_min)
            {
                return false;
            }

            return true;
        }

        template <>
        bool isType<i8>(const nlohmann::json &jsonObj)
        {
            if (!jsonObj.is_number_integer())
            {
                return false;
            }

            i32 value = jsonObj.get<i32>();

            if (value > i8_max || value < i8_min)
            {
                return false;
            }

            return true;
        }

        template <>
        bool isType<u16>(const nlohmann::json &jsonObj)
        {
            if (!jsonObj.is_number_unsigned())
            {
                return false;
            }

            u32 value = jsonObj.get<u32>();

            if (value > u16_max)
            {
                return false;
            }

            return true;
        }

        template <>
        bool isType<i16>(const nlohmann::json &jsonObj)
        {
            if (!jsonObj.is_number_integer())
            {
                return false;
            }

            i32 value = jsonObj.get<i32>();

            if (value > i16_max || value < i16_min)
            {
                return false;
            }

            return true;
        }

        template <>
        bool isType<String>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_string();
        }

        template <>
        bool isType<JSON>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_object();
        }

        template <>
        bool isType<f32>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_number_float() || jsonObj.is_number_integer();
        }

        template <>
        bool isType<f64>(const nlohmann::json &jsonObj)
        {
            return jsonObj.is_number_float() || jsonObj.is_number_integer();
        }
    } // namespace internal

    class JSON::JSONPrivate
    {
    public:
        nlohmann::json jsonObj;
    };

    JSON::JSON()
    {
        impl = CreateScope<JSONPrivate>();
    }

    JSON::JSON(const JSON &other)
    {
        impl = CreateScope<JSONPrivate>();
        impl->jsonObj = other.impl->jsonObj;
    }

    JSON::JSON(JSON &&other)
    {
        impl = std::move(other.impl);
    }

    JSON::~JSON() = default;

    JSON &JSON::operator=(const JSON &other)
    {
        if (this != &other)
        {
            impl = CreateScope<JSONPrivate>();
            impl->jsonObj = other.impl->jsonObj;
        }
        return *this;
    }

    JSON JSON::parse(const String &str)
    {
        try
        {
            nlohmann::json obj = nlohmann::json::parse(str);

            JSON jsonObj;
            jsonObj.impl->jsonObj = obj;

            return jsonObj;
        }
        catch (const nlohmann::json::parse_error &e)
        {
            throw std::runtime_error("JSON parse error: " + String(e.what()));
        }
    }

    String JSON::dump() const
    {
        return impl->jsonObj.dump(4); // 4 spaces for indentation
    }

    std::vector<String> JSON::keys() const
    {
        std::vector<String> keys;
        for (const auto &item : impl->jsonObj.items())
        {
            keys.push_back(item.key());
        }

        return keys;
    }

#define IS_TYPE_DEF(type)                                         \
    template <>                                                   \
    bool JSON::isType<type>(const String &key) const              \
    {                                                             \
        try                                                       \
        {                                                         \
            return internal::isType<type>(impl->jsonObj.at(key)); \
        }                                                         \
        catch (const nlohmann::json::exception &e)                \
        {                                                         \
            return false;                                         \
        }                                                         \
    }

#define GET_TYPE_DEF(type)                                                  \
    template <>                                                             \
    type JSON::get<type>(const String &key, const type &defaultValue) const \
    {                                                                       \
        if (!isType<type>(key))                                             \
        {                                                                   \
            return defaultValue;                                            \
        }                                                                   \
        try                                                                 \
        {                                                                   \
            return impl->jsonObj.at(key).get<type>();                       \
        }                                                                   \
        catch (const nlohmann::json::exception &e)                          \
        {                                                                   \
            return defaultValue;                                            \
        }                                                                   \
    }

    IS_TYPE_DEF(bool)
    GET_TYPE_DEF(bool)

    IS_TYPE_DEF(u32)
    GET_TYPE_DEF(u32)

    IS_TYPE_DEF(i32)
    GET_TYPE_DEF(i32)

    IS_TYPE_DEF(u8)
    GET_TYPE_DEF(u8)

    IS_TYPE_DEF(i8)
    GET_TYPE_DEF(i8)

    IS_TYPE_DEF(u16)
    GET_TYPE_DEF(u16)

    IS_TYPE_DEF(i16)
    GET_TYPE_DEF(i16)

    IS_TYPE_DEF(f32)
    GET_TYPE_DEF(f32)

    IS_TYPE_DEF(f64)
    GET_TYPE_DEF(f64)

    IS_TYPE_DEF(String)
    GET_TYPE_DEF(String)

    IS_TYPE_DEF(JSON)
    template <>
    JSON JSON::get<JSON>(const String &key, const JSON &defaultValue) const
    {
        try
        {
            if (!isType<JSON>(key))
            {
                return defaultValue;
            }

            nlohmann::json jsonObj = impl->jsonObj.at(key);
            JSON result;
            result.impl->jsonObj = jsonObj;
            return result;
        }
        catch (const nlohmann::json::exception &e)
        {
            return defaultValue;
        }
    }

    bool JSON::isList(const String &key) const
    {
        try
        {
            return impl->jsonObj.at(key).is_array();
        }
        catch (const nlohmann::json::exception &e)
        {
            return false;
        }
    }

#define GET_LIST_TYPE_DEF(type)                                    \
    template <>                                                    \
    std::vector<type> JSON::getList<type>(const String &key) const \
    {                                                              \
        if (!isList(key))                                          \
        {                                                          \
            return {};                                             \
        }                                                          \
                                                                   \
        nlohmann::json list = impl->jsonObj.at(key);               \
                                                                   \
        std::vector<type> resultList;                              \
        for (const auto &item : list)                              \
        {                                                          \
            if (internal::isType<type>(item))                      \
            {                                                      \
                resultList.push_back(item.get<type>());            \
            }                                                      \
        }                                                          \
                                                                   \
        return resultList;                                         \
    }

    GET_LIST_TYPE_DEF(bool)
    GET_LIST_TYPE_DEF(u32)
    GET_LIST_TYPE_DEF(i32)
    GET_LIST_TYPE_DEF(u8)
    GET_LIST_TYPE_DEF(i8)
    GET_LIST_TYPE_DEF(u16)
    GET_LIST_TYPE_DEF(i16)
    GET_LIST_TYPE_DEF(f32)
    GET_LIST_TYPE_DEF(f64)
    GET_LIST_TYPE_DEF(String)

    template <>
    std::vector<JSON> JSON::getList<JSON>(const String &key) const
    {
        if (!isList(key))
        {
            return {};
        }

        nlohmann::json list = impl->jsonObj.at(key);

        std::vector<JSON> resultList;
        for (const auto &item : list.items())
        {
            if (internal::isType<JSON>(item))
            {
                nlohmann::json jsonObj = item.value();
                JSON result;
                result.impl->jsonObj = jsonObj;
                resultList.push_back(result);
            }
        }

        return resultList;
    }

    // format json object to string
    template <>
    String format(const String &formatMsg, const JSON &jsonObj)
    {
        return format(formatMsg, jsonObj.dump());
    }
} // namespace NTT_NS
