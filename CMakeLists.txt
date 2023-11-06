cmake_minimum_required(VERSION 3.24)
project(ProjetAgenda C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetAgenda main.c levels_cell.c levels_cell.h levels_list.c levels_list.h)
