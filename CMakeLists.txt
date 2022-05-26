cmake_minimum_required(VERSION 2.8.12)
project(cpp_base_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(include)

file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCE_FILES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCE_FILES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/main.cpp)
set(SOURCE_FILES ${SOURCE_FILES_NO_MAIN} ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC inih )
include(${CMAKE_SOURCE_DIR}/cmake/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang_tools.cmake)
