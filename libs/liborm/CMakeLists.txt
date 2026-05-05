cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

add_library(liborm SHARED)

target_include_directories(liborm
    PUBLIC
        include/
)

add_subdirectory(src)
