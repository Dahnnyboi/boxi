cmake_minimum_required(VERSION 3.16)
project(boxi)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)

add_executable(boxi
  src/main.cpp
  external/glad/src/glad.c
)

target_include_directories(boxi PRIVATE external/glad/include)
target_link_libraries(boxi glfw)