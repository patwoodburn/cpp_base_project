cmake_minimum_required(VERSION 2.8.12)
project(some_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CONAN_SYSTEM_INCLUDES ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)

file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCE_FILES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCE_FILES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/main.cpp)
set(SOURCE_FILES ${SOURCE_FILES_NO_MAIN} ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(some_test ${SOURCE_FILES})
target_link_libraries(some_test ${CONAN_LIBS})

include(${CMAKE_SOURCE_DIR}/cmake/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
