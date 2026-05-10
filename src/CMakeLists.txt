cmake_minimum_required(VERSION 3.25)

option(ABREGEFEUR_ENABLE_QT_DEPLOY "Install abregefeur with Qt deploy" OFF)

include(GNUInstallDirs)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Quick Qml Sql)

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
        liborm
        AbregeFeur::Triggers
        abregefeur_qmlplugin
)

install(TARGETS abregefeur
    BUNDLE
        DESTINATION .
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (ABREGEFEUR_ENABLE_QT_DEPLOY)
    qt_generate_deploy_qml_app_script(TARGET abregefeur
        OUTPUT_SCRIPT
            deploy_script
    )
    install(SCRIPT ${deploy_script})
endif()
