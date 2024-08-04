cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C++_COMPILER_ENV_VAR)
set(CMAKE_C++_COMPILER "/usr/bin/g++")

project(hello)
# CMake_C++_COMPILER(/usr/bin/g++)
add_executable(app.exe src/main.cpp)
