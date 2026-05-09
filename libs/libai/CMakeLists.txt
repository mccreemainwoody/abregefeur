cmake_minimum_required(VERSION 3.25)

option(LIBAI_USE_STATIC_LIBS "Build libai as a static library" OFF)

find_package(CURL 8.19.0 REQUIRED COMPONENTS HTTPS)
find_package(nlohmann_json 3.12.0 REQUIRED)

if (LIBAI_USE_STATIC_LIBS)
    add_library(libai STATIC)
else()
    add_library(libai SHARED)
endif()

target_include_directories(libai
    PUBLIC
        include/
    PRIVATE
        detail/
)

add_subdirectory(src)
