cmake_minimum_required(VERSION 4.1)

#set(CMAKE_C_FLAGS lSDL3)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL3")

project(jamejam)

set(CMAKE_CXX_STANDARD 20)

add_executable(jamejam src/main.cpp
        src/resource_location.h
        src/resource_location.cpp
        src/serializable_field.h
        src/util.h
        src/serializable_field.cpp
)


target_link_libraries(jamejam SDL3 SDL3_ttf SDL3_image)