cmake_minimum_required(VERSION 3.24)
project(LabAssemblerProject C)

set(CMAKE_C_STANDARD 90)

#add_subdirectory(pre)
#add_subdirectory(assembly)

add_executable(main
        main.c
        main.h

        root.h

        libs/linkedlist/linked_list.h
        libs/linkedlist/linked_list.c

        libs/data/data.c
        libs/data/data.h

        libs/io/io.c
        libs/io/io.h

        libs/instruction/instruction.c
        libs/instruction/instruction.h

        libs/label/label.c
        libs/label/label.h

        libs/macro/macro.c
        libs/macro/macro.h

        assembly/assembly.c
        assembly/assembly.h

        assembly/phase1.h
        assembly/phase1.c

        pre/pre.h
        pre/pre.c
        libs/datatypes.h)

#target_link_libraries(main
#        pre
#        assembly)