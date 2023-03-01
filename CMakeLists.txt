cmake_minimum_required(VERSION 3.24)
project(LabAssemblerProject C)

set(CMAKE_C_STANDARD 90)

add_subdirectory(pre)
add_subdirectory(assembly)

add_executable(main
        main.c
        main.h
)

target_link_libraries(main
        pre
        assembly)