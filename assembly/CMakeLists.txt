add_library(assembly "" )

target_sources(assembly PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/label.c
        ${CMAKE_CURRENT_SOURCE_DIR}/assembly.h
        ${CMAKE_CURRENT_SOURCE_DIR}/assembly.c
        ${CMAKE_CURRENT_SOURCE_DIR}/phase1.c
        ${CMAKE_CURRENT_SOURCE_DIR}/phase2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/phase1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/phase2.h
        )

target_include_directories(assembly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})