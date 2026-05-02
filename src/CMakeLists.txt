cmake_minimum_required(VERSION 3.25)

qt_add_executable(abregefeur
    main.cpp
)

add_subdirectory(utils)
add_subdirectory(data)
add_subdirectory(handlers)

qt_add_qml_module(abregefeur
    URI AbregeFeur
    VERSION 1.0
    QML_FILES
        qml/Artifacts.qml
        qml/Colors.qml
        qml/Main.qml
        qml/Notes.qml
        qml/Sources.qml
)

target_link_libraries(abregefeur
    PRIVATE
        abregefeur_data
        abregefeur_handlers
        Qt6::Quick
)
