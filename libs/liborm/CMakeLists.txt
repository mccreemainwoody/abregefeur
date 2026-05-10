cmake_minimum_required(VERSION 3.25)

option(LIBORM_USE_STATIC_LIBS "Build liborm as a static library" OFF)

set(LIBORM_LIBRARY_VERSION 0.1.0)
set(LIBORM_LIBRARY_VERSION_MAJOR 0)

include(GNUInstallDirs)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Sql)

if (LIBORM_USE_STATIC_LIBS)
    add_library(liborm STATIC)
else()
    add_library(liborm SHARED)
endif()

set_target_properties(liborm PROPERTIES
    LIBRARY_OUTPUT_NAME orm
    VERSION ${LIBORM_LIBRARY_VERSION}
    SOVERSION ${LIBORM_LIBRARY_VERSION_MAJOR}
)

target_include_directories(liborm
    PUBLIC
        include/
    PRIVATE
        detail/
)

add_subdirectory(src)

install(TARGETS liborm
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
