cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Qml)

qt_add_library(abregefeur_triggers STATIC)

qt_add_qml_module(abregefeur_triggers
    URI AbregeFeur.Triggers
    VERSION 1.0
    OUTPUT_DIRECTORY AbregeFeur/Triggers
    SOURCES
        note_view.cpp
        note_view.hpp
        notes_triggers.cpp
        notes_triggers.hpp
)

target_link_libraries(abregefeur_triggers
    PUBLIC
        Qt6::Core
        Qt6::Qml
        abregefeur_data
        abregefeur_handlers
)
