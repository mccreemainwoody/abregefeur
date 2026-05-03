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

target_link_libraries(abregefeur
    PRIVATE
        Qt6::Quick
        libai
        abregefeur_data
        abregefeur_handlers
        abregefeur_triggersplugin
        abregefeur_qmlplugin
)
