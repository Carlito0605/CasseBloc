cmake_minimum_required(VERSION 3.20)
project(CasseBloc)

set(CMAKE_C_STANDARD 99)

add_executable(CasseBloc main.c bombs.c bombs.h menu.c menu.h)