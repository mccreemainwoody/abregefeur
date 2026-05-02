cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

add_library(abregefeur_data STATIC
    note.cpp
    note.hpp
)

target_include_directories(abregefeur_data
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(abregefeur_data
    PRIVATE
        Qt6::Core
        Qt6::Sql
        abregefeur_utils
)
