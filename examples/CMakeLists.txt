# Each .cpp file in the current folder will represent a separate example, these
#   examples are the ones that cannot be tested with the testing framework.

file(
    GLOB
    EXAMPLES_SOURCE_FILES
    *.cpp
)

foreach(EXAMPLES_SOURCE_FILE ${EXAMPLES_SOURCE_FILES})
    get_filename_component(EXAMPLES_TARGET_NAME ${EXAMPLES_SOURCE_FILE} NAME_WE)
    add_executable(
        ${EXAMPLES_TARGET_NAME}
        ${EXAMPLES_SOURCE_FILE}
    )

    target_link_libraries(
        ${EXAMPLES_TARGET_NAME}
        PRIVATE
        ${PROJECT_NAME}
    )
endforeach()
