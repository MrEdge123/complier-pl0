cmake_minimum_required(VERSION 3.19)
project(pl0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pl0
        pl0.c
        pl0.h)
