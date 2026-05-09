cmake_minimum_required(VERSION 3.25)

project(abregefeur VERSION 1.0.0 LANGUAGES CXX)

option(USE_STATIC_LIBS "Build project libs as static instead of shared" OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBAI_USE_STATIC_LIBS
    ${USE_STATIC_LIBS}
    CACHE BOOL "Build libai as a static library"
)

set(LIBORM_USE_STATIC_LIBS
    ${USE_STATIC_LIBS}
    CACHE BOOL "Build liborm as a static library"
)

add_subdirectory(libs/libai)
add_subdirectory(libs/liborm)
add_subdirectory(src)
