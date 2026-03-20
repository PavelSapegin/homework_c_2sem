cmake_minimum_required(VERSION 3.13)
project(task2 C)

set(CURR_DIR ./src/task2)
add_executable(airports ${CURR_DIR}/main.c ${CURR_DIR}/avl.c ${CURR_DIR}/interface.c ${CURR_DIR}/test.c)
target_compile_options(airports PRIVATE -Wall -Wextra -Wpedantic)

add_executable(avl_bench ${CURR_DIR}/avl.c ${CURR_DIR}/interface.c ${CURR_DIR}/benchmarks.c)
add_executable(list_bench ${CURR_DIR}/list.c ${CURR_DIR}/benchmarks.c)
target_compile_options(avl_bench PRIVATE -g -O0)
target_compile_options(list_bench PRIVATE -g -O0)
