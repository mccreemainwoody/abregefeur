cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Quick Sql)

qt_standard_project_setup(REQUIRES 6.10)
qt_policy(SET QTP0005 NEW)

qt_add_executable(abregefeur
    main.cpp
)

add_subdirectory(utils)
add_subdirectory(data)
add_subdirectory(handlers)
add_subdirectory(triggers)
add_subdirectory(qml)

add_library(AbregeFeur::Utils    ALIAS abregefeur_utils)
add_library(AbregeFeur::Data     ALIAS abregefeur_data)
add_library(AbregeFeur::Handlers ALIAS abregefeur_handlers)
add_library(AbregeFeur::Triggers ALIAS abregefeur_triggers)
add_library(AbregeFeur::Qml      ALIAS abregefeur_qml)

target_link_libraries(abregefeur
    PRIVATE
        Qt6::Quick
        AbregeFeur::Utils
        AbregeFeur::Data
        AbregeFeur::Handlers
        abregefeur_qmlplugin
)
