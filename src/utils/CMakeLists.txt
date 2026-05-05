cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

add_library(abregefeur_utils STATIC)

target_include_directories(abregefeur_utils
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/detail
)
