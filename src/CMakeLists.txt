cmake_minimum_required(VERSION 3.25)

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
        abregefeur_data
        abregefeur_handlers
        abregefeur_triggersplugin
        abregefeur_qmlplugin
)
