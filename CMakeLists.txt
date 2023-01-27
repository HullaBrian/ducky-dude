cmake_minimum_required(VERSION 3.24)
project(ducky_dude C)

set(CMAKE_C_STANDARD 11)

include_directories(ducky-dude)

add_executable(ducky_dude
        ducky-dude/ducky.c)
