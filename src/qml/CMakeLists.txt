cmake_minimum_required(VERSION 3.25)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Quick)

qt_add_library(abregefeur_qml STATIC)

qt_add_qml_module(abregefeur_qml
    URI AbregeFeur
    VERSION 1.0
    OUTPUT_DIRECTORY AbregeFeur
    QML_FILES
        Artifacts.qml
        Colors.qml
        Main.qml
        Notes.qml
        Sources.qml
)

target_link_libraries(abregefeur_qml
    PRIVATE
        abregefeur_triggersplugin
)
