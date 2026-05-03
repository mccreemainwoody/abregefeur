cmake_minimum_required(VERSION 3.25)

find_package(CURL 8.19.0 REQUIRED COMPONENTS HTTPS)

add_library(libai SHARED)

target_include_directories(libai
    PUBLIC
        include/
)

add_subdirectory(src)
