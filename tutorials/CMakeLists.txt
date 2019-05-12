cmake_minimum_required(VERSION 3.0)
project(tutorials)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 14)

add_executable(types tutorial01/types.cpp)

add_executable(
        workshop01
        workshops/Random.cpp
        workshops/workshop01/workshop01.cpp
        workshops/workshop01/Multiplicator.cpp
        workshops/workshop01/Number.cpp
        workshops/workshop01/NumberTests.cpp
        workshops/workshop01/MultiplicatorTests.cpp
        )

add_executable(
        workshop02
        workshops/Random.cpp
        workshops/workshop02/workshop02.cpp
        )
