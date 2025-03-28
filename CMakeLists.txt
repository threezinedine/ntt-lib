cmake_minimum_required(VERSION 3.10)
project(NTTLib)

set(CMAKE_CXX_STANDARD 14)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(NTTLib_USE_EXAMPLES "Enable examples" OFF)
option(NTTLib_USE_TESTS "Enable tests" OFF)

file(
    GLOB_RECURSE
    CPP_SOURCE_FILES
    src/*.cpp
)

file(
    GLOB_RECURSE
    HEADER_FILES
    src/*.hpp
)

set(
    MAIN_HEADER
    include/NTTLib.hpp
)

set(
    EXTERNAL_LIBS 
)

set(CMAKE_FOLDER "vendors")
add_subdirectory(vendors)
unset(CMAKE_FOLDER)

set(
    COMMON_DEFINITIONS
)

if (UNIX)
    set(
        COMMON_DEFINITIONS  
        ${COMMON_DEFINITIONS}
        -DNTT_PLATFORM_UNIX
    )
else()
    set(
        COMMON_DEFINITIONS
        ${COMMON_DEFINITIONS}
        -DNTT_PLATFORM_WINDOWS
    )
endif()

if (MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available build configurations" FORCE)
    set_property(CACHE CMAKE_CONFIGURATION_TYPES PROPERTY STRINGS "Debug" "Release")

    set(
        COMMON_DEFINITIONS
        ${COMMON_DEFINITIONS}
        -DNTT_MSVC
        $<$<CONFIG:Debug>:NTT_DEBUG>
        $<$<CONFIG:Release>:NTT_NDEBUG>
    )
else()
    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -Wswitch-enum
        -Wcast-align
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(
            COMMON_DEFINITIONS
            ${COMMON_DEFINITIONS}
            -DNTT_DEBUG
        )
    else()
        set(
            COMMON_DEFINITIONS
            ${COMMON_DEFINITIONS}
            -DNTT_NDEBUG
        )
    endif()
endif()

# library target
add_library(
    ${PROJECT_NAME}
    STATIC
    ${CPP_SOURCE_FILES}
    ${HEADER_FILES}
    ${MAIN_HEADER}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
    ./src
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${EXTERNAL_LIBS}
)

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
    ${COMMON_DEFINITIONS}
)

if (NTTLib_USE_TESTS)
    # library testing target
    file(
        GLOB_RECURSE
        TEST_SOURCE_FILES
        test/*.cpp
    )

    set(TEST_PROJECT_NAME ${PROJECT_NAME}_test)

    add_executable(
        ${TEST_PROJECT_NAME}
        ${TEST_SOURCE_FILES}
    )

    target_include_directories(
        ${TEST_PROJECT_NAME}
        PRIVATE
        include
    )

    target_link_libraries(
        ${TEST_PROJECT_NAME}
        PUBLIC
        ${EXTERNAL_LIBS}
        ${PROJECT_NAME}
        PRIVATE
        gtest 
        gmock
    )

    target_compile_definitions(
        ${TEST_PROJECT_NAME}
        PUBLIC
        ${COMMON_DEFINITIONS}
    )
endif()

if (NTTLib_USE_EXAMPLES)
    # examples target
    set(CMAKE_FOLDER "examples")
    add_subdirectory(examples)
    unset(CMAKE_FOLDER)
endif()