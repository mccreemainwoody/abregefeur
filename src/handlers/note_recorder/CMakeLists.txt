cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core)

target_sources(abregefeur_handlers
    PRIVATE
        note_recorder.cpp
)

target_link_libraries(abregefeur_handlers
    PRIVATE
        Qt6::Core
        abregefeur_data
)
