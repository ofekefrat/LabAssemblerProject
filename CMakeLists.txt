cmake_minimum_required(VERSION 3.24)
project(LabAssemblerProject C)

set(CMAKE_C_STANDARD 90)

include_directories(src)

add_executable(main
        src/main.c
        src/preassemble.c
        src/mcr.c
        src/preassemble.h
)