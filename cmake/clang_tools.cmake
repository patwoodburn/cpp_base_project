message(${CONAN_INCLUDE_DIRS})
find_program(CLANG_TIDY NAMES clang-tidy clang-tidy-6.0)
if (CLANG_TIDY)
    add_custom_target(
            clang-tidy
            COMMAND ${CLANG_TIDY}
            ${SOURCE_FILES}
            -p compile_commands.json
            --
            -std=c++11
            -I ${CMAKE_SOURCE_DIR}/include
            -I ${CONAN_INCLUDE_DIRS}
    )
endif ()


find_program(CLANG_FORMAT NAMES clang-format clang-format-6.0)
if (CLANG_FORMAT)
    add_custom_target(
            clang-format
            COMMAND ${CLANG_FORMAT}
            -i
            ${SOURCE_FILES} ${TEST_SOURCE_FILES}
    )
endif ()