cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Sql)

add_library(abregefeur_data STATIC
    note.cpp
)

target_include_directories(abregefeur_data
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/detail
)

target_link_libraries(abregefeur_data
    PUBLIC
        Qt6::Core
        Qt6::Sql
        liborm
)
