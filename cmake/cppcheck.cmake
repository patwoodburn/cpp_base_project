find_program(CPPCHECK cppcheck)
if (CPPCHECK)
    add_custom_target(
            cppcheck
            COMMAND ${CPPCHECK}
            --quiet
            --error-exitcode=1
            --enable=warning,portability,performance,style
            --std=c++17
            -I ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
            ${CONAN_LIBS}
    )
endif ()