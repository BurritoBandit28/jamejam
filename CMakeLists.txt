cmake_minimum_required(VERSION 4.1)

project(jamejam)

set(CMAKE_CXX_STANDARD 20)

add_executable(jamejam src/main.cpp
        src/resource_location.h
        src/resource_location.cpp
        src/serializable_field.h
        src/util.h
        src/serializable_field.cpp)
