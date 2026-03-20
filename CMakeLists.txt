cmake_minimum_required(VERSION 3.13)
project(task2 C)

set(CURR_DIR ./src/task2)
add_executable(airports ${CURR_DIR}/main.c ${CURR_DIR}/avl.c ${CURR_DIR}/interface.c ${CURR_DIR}/test.c)
target_compile_options(airports PRIVATE -Wall -Wextra -Wpedantic)
