cmake_minimum_required(VERSION 3.13)
project(task3 C)

set(CURR_DIR ./src/task3)
add_executable(expansion ${CURR_DIR}/main.c ${CURR_DIR}/expansion.c ${CURR_DIR}/tests.c)
target_compile_options(expansion PRIVATE -Wall -Wextra -Wpedantic)
