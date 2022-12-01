cmake_minimum_required(VERSION 3.23)
project(aoc)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc main.cpp)

target_compile_options(aoc PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
