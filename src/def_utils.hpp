#pragma once
#include "memory.hpp"

/**
 * Used in class definition which will hide all the private operations, properties
 *      and methods of a class, they will not be visible in the header file.
 *
 * This is useful when you want to hide the implementation details of a class and
 *      only expose the public interface.
 */
#define NTT_PRIVATE_DEF(cls) \
private:                     \
    class cls##Private;      \
    Scope<cls##Private> impl
