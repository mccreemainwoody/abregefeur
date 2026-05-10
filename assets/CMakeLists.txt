cmake_minimum_required(VERSION 3.25)

include(GNUInstallDirs)

if(UNIX AND NOT APPLE)
    install(
        FILES
            abregefeur.desktop
        DESTINATION
            ${CMAKE_INSTALL_DATADIR}/applications
    )
endif()
