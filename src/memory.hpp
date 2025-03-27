#pragma once
#include "common.hpp"
#include <memory>
#include "format.hpp"

namespace NTT_NS
{
    /**
     * The alias for the unique pointer.
     */
    template <typename T>
    using Scope = std::unique_ptr<T>;

    /**
     * The creation of the unique pointer.
     */
    template <typename T, typename... Args>
    Scope<T> CreateScope(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    String format(const String &formatMsg, const Scope<T> &ptr)
    {
        return format(formatMsg, format("<Scope value={} />", *ptr.get()));
    }

    /**
     * The alias for the shared pointer.
     */
    template <typename T>
    using Ref = std::shared_ptr<T>;

    /**
     * The creation of the shared pointer.
     */
    template <typename T, typename... Args>
    Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    String format(const String &formatMsg, const Ref<T> &ptr)
    {
        return format(formatMsg, format("<Ref value={} />", *ptr.get()));
    }
} // namespace NTT_NS
