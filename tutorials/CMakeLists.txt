cmake_minimum_required(VERSION 3.0)
project(tutorials)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 11)

add_executable(types tutorial01/types.cpp)
add_executable(workshop01 workshop01/workshop01.cpp
                          workshop01/Multiplicator.cpp
                          workshop01/Random.cpp
                          workshop01/Number.cpp)
