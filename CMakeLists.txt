cmake_minimum_required(VERSION 3.24)
project(LabAssemblerProject C)

set(CMAKE_C_STANDARD 90)

add_subdirectory(src)

#add_executable(main
#        src/main/main.c
#        src/main/main.h
#
#        src/root.h
#
#        src/libs/linkedlist/linked_list.h
#        src/libs/linkedlist/linked_list.c
#
#        src/libs/data/data.c
#        src/libs/data/data.h
#
#        src/libs/io/io.c
#        src/libs/io/io.h
#
#        src/libs/instruction/instruction.c
#        src/libs/instruction/instruction.h
#
#        src/libs/label/label.c
#        src/libs/label/label.h
#
#        src/libs/macro/macro.c
#        src/libs/macro/macro.h
#
#        src/assembly/assembly.c
#        src/assembly/assembly.h
#
#        src/assembly/phase1.c
#        src/assembly/phase2.c
#
#        src/pre/pre.h
#        src/pre/pre.c
#
#        src/libs/data_types.h
#        )
#
#add_executable(test
#        src/root.h
#
#        src/libs/linkedlist/linked_list.h
#        src/libs/linkedlist/linked_list.c
#
#        src/libs/data/data.c
#        src/libs/data/data.h
#
#        src/libs/io/io.c
#        src/libs/io/io.h
#
#        src/libs/instruction/instruction.c
#        src/libs/instruction/instruction.h
#
#        src/libs/label/label.c
#        src/libs/label/label.h
#
#        src/libs/macro/macro.c
#        src/libs/macro/macro.h
#
#        src/assembly/assembly.c
#        src/assembly/assembly.h
#
#        src/assembly/phase1.c
#
#        src/pre/pre.h
#        src/pre/pre.c
#        src/libs/data_types.h src/assembly/phase2.c src/main/test.c)
