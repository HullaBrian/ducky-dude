cmake_minimum_required(VERSION 3.24)
project(ducky_dude C)

set(CMAKE_C_STANDARD 11)

include_directories(ducky-dude)

add_executable(ducky_dude
        ducky-dude/ducky.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb-1.0 REQUIRED libusb-1.0)
