cmake_minimum_required(VERSION 3.13)
project(task2 C)

add_executable(airports main.c avl.c interface.c)
target_compile_options(airports PRIVATE -Wall -Wextra -Wpedantic)
