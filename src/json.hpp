#pragma once
#include "common.hpp"
#include "memory.hpp"
#include "def_utils.hpp"
#include <vector>
#include "format.hpp"

namespace NTT_NS
{
    class JSON
    {
    public:
        JSON();
        JSON(const JSON &);
        JSON(JSON &&);
        ~JSON();

        JSON &operator=(const JSON &);

        /**
         * Extract a new object from a string with the correct JSON
         *      format. If the string is not a valid JSON, it will throw an exception.
         *
         * @param str The string to be extracted.
         * @return A new JSON object.
         */
        static JSON parse(const String &str);

        /**
         * Convert the current JSON object into a string with the correct JSON
         *      format. The string will have the format with each element will
         *      be in one line, tabbed with 4 spaces.
         *
         * @return A string with the correct JSON format.
         *
         * @example
         * ```C++
         * JSON json = JSON::parse("{\"key\": \"value\"}");
         * String str = json.dump();
         * // str will be:
         * // {
         * //     "key": "value"
         * // }
         * ```
         */
        String dump() const;

        /**
         * Checking the type of the current item.
         * Only supports the primitive types (like bool, u8, u16, u32, u64, i8,
         *      i16, i32, i64, f32, f64, String, JSON)
         *
         * @param key The key of the current item with the given key.
         * @tparam T The type of the current item which will be checked and be one of the primitive types
         *      which are provided as above.
         * @retval true If the type of the current item is the same as the template parameter.
         * @retval false Otherwise.
         *
         * @example
         * ```C++
         * JSON json = JSON::parse("{\"key\": \"value\"}");
         * bool isString = json.isType<String>("key");
         * // isString will be true
         * ```
         */
        template <typename T>
        bool isType(const String &key = NTT_STRING_EMPTY) const;

        /**
         * Check if the current JSON object is a list or not.
         *
         * @param key The key of the current item with the given key.
         * @retval true If the current JSON object is a list.
         * @retval false Otherwise.
         *
         * @example
         * ```C++
         * JSON json = JSON::parse("{\"key\": [1, 2, 3]}");
         * bool isList = json.isList("key");
         * // isList will be true
         * ```
         */
        bool isList(const String &key) const;

        /**
         * Get the value of the JSON object value with the given key.
         * If the key is not found or any conversion error occurs, it will
         *      return the default value of the type.
         *
         * @tparam T The type can be only: bool, U8, U16, U32, U64,
         *      I8, I16, I32, I64, F32, F64, String, JSON.
         *      Other types will throw an exception.
         *
         * @param key The key to be searched in the JSON object.
         * @param defaultValue The default value to be returned if the key is not found.
         *      or any conversion error occurs.
         * @return The value of the JSON object with the given key.
         */
        template <typename T>
        T get(const String &key, const T &defaultValue) const;

        /**
         * Obtain all the keys of the current object.
         *
         * @return A vector which will contain all the keys of the current object (
         *      not including the keys of the nested objects).
         */
        std::vector<String> keys() const;

        /**
         * Self convert to a list (vector) of a certain type.
         *
         * @return A vector which contains all elements in the current JSON object which
         *      has the same type as the template parameter.
         *
         * @example
         * ```C++
         * JSON json = JSON::parse("{\"key\": [1, 2, "Hello World", 3]}");
         * std::vector<u32> list = json.getList<u32>("key");
         * ```
         */
        template <typename T>
        std::vector<T> getList(const String &key) const;

    private:
        NTT_PRIVATE_DEF(JSON);
    };

    /**
     * Format the JSON object to a string.
     *
     * @param formatMsg The format message.
     * @param jsonObj The JSON object to be formatted.
     * @return A string with the formatted JSON object.
     */
    template <>
    String format(const String &formatMsg, const JSON &jsonObj);
} // namespace NTT_NS
