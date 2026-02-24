cmake_minimum_required(VERSION 3.13)
project(task1 C)

set(CURR_DIR ./src/task1)


add_executable(readcsv ${CURR_DIR}/readcsv.c ${CURR_DIR}/main.c ${CURR_DIR}/tests.c)
target_compile_options(readcsv PUBLIC -Wall -Wextra -Wpedantic)
