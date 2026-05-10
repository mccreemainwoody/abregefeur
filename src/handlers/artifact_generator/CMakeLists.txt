cmake_minimum_required(VERSION 3.25)

target_include_directories(abregefeur_handlers
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(abregefeur_handlers
    PRIVATE
        artifact_generator.cpp
)

target_link_libraries(abregefeur_handlers
    PUBLIC
        Qt6::Core
        libai
        abregefeur_data
    PRIVATE
        liborm
)

