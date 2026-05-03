cmake_minimum_required(VERSION 3.25)

find_package(CURL 8.19.0 REQUIRED COMPONENTS HTTPS)
find_package(nlohmann_json 3.12.0 REQUIRED)

add_library(libai SHARED)

target_include_directories(libai
    PUBLIC
        include/
    PRIVATE
        detail/
)

add_subdirectory(src)
