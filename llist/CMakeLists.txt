cmake_minimum_required(VERSION 3.12)
project(llist C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wall -Werror")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)

enable_testing()

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(CHECK REQUIRED check)

add_subdirectory(tests)

set(STUDENT
        student/llist.c
        tests/main.c
        )
include_directories(student)
add_executable(student ${STUDENT})
target_link_libraries(student m  ${CHECK_LIBRARIES})