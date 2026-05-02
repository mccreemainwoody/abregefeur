cmake_minimum_required(VERSION 3.16)

add_library(abregefeur_utils STATIC
    timestamp.hpp
    timestamp.hxx
)

target_include_directories(abregefeur_utils
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(abregefeur_utils
    PUBLIC
        Qt6::Core
)
