cmake_minimum_required(VERSION 3.24)
project(LabAssemblerProject C)

set(CMAKE_C_STANDARD 90)

include_directories(*)

add_executable(LabAssemblerProject
        main.h main.c cell/cell.c)
