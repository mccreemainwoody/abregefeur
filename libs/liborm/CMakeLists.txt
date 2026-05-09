cmake_minimum_required(VERSION 3.25)

option(LIBORM_USE_STATIC_LIBS "Build liborm as a static library" OFF)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

if (LIBORM_USE_STATIC_LIBS)
    add_library(liborm STATIC)
else()
    add_library(liborm SHARED)
endif()

target_include_directories(liborm
    PUBLIC
        include/
    PRIVATE
        detail/
)

add_subdirectory(src)
