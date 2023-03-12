add_executable(main
        main/main.c
        main/main.h

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

        assembly/phase1.c
        assembly/phase2.c

        pre/pre.h
        pre/pre.c

        libs/data_types.h
        )

add_executable(test
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

        assembly/phase1.c

        pre/pre.h
        pre/pre.c
        libs/data_types.h assembly/phase2.c main/test.c)
