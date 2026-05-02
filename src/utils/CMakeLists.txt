cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

add_library(abregefeur_utils STATIC
    timestamp.hpp
    timestamp.hxx
)

target_include_directories(abregefeur_utils
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(abregefeur_utils
    PRIVATE
        Qt6::Core
)
