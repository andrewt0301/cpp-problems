cmake_minimum_required(VERSION 2.8)

project(hello_world)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB foo.cpp)

add_library(foo STATIC ${SOURCE_LIB})

add_executable(hello ${SOURCE_EXE})

target_link_libraries(hello foo)

