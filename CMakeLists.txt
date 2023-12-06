cmake_minimum_required(VERSION 3.24)
project(untitled C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled main.c cell.h list.c list.h partie3.c partie3.h timer.h cell.c timer.c)
