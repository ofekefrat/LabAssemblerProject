add_library(pre "")

target_sources(pre PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/pre.c
            ${CMAKE_CURRENT_SOURCE_DIR}/mcr.c
            ${CMAKE_CURRENT_SOURCE_DIR}/pre.h
        )

target_include_directories(pre PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})