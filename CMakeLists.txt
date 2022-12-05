cmake_minimum_required(VERSION 3.23)
project(advent-of-code-2022)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

add_subdirectory(day-01)
add_subdirectory(day-02)
add_subdirectory(day-03)
add_subdirectory(day-04)
add_subdirectory(day-05)
