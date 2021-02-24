file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(unit_test ${SOURCE_FILES_NO_MAIN} ${TEST_SOURCE_FILES})

# Enable CMake `make test` support.
enable_testing()
add_test(NAME UnitTests COMMAND unit_test -r junit -o results.xml)