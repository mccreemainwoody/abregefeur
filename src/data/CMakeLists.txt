cmake_minimum_required(VERSION 3.16)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

add_library(abregefeur_data STATIC
    note.cpp
    note.hpp
)

target_link_libraries(abregefeur_data
    PUBLIC
        Qt6::Core
        Qt6::Sql
)
