cmake_minimum_required(VERSION 3.24)
project(untitled C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled timer.h timer.c main.c  list.c main.c agenda.c agenda.h main.c)
