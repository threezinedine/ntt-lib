# Load all vendors, these vendors will not be visible to the user
# but will be used by the build system to build the project

# Add all vendors here

if (NOT NTTLib_USE_ONLY)
    if (MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT" FORCE)
    endif()

    add_subdirectory(googletest EXCLUDE_FROM_ALL)
endif()