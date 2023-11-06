cmake_minimum_required(VERSION 3.24)
project(ProjetAgenda C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetAgenda main.c cell.c cell.h list.c list.h)
