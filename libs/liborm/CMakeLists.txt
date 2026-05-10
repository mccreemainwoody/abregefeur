cmake_minimum_required(VERSION 3.25)

option(LIBORM_USE_STATIC_LIBS "Build liborm as a static library" OFF)

set(LIBORM_LIBRARY_VERSION 0.1.0)
set(LIBORM_LIBRARY_VERSION_MAJOR 0)

include(CMakePackageConfigHelpers)
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        detail/
)

add_subdirectory(src)

install(TARGETS liborm
    EXPORT
        libormTargets
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
install(EXPORT libormTargets
    NAMESPACE AbregeFeur::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/liborm
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/libormConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/libormConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/liborm
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/libormConfigVersion.cmake
    VERSION ${LIBORM_LIBRARY_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libormConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/libormConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/liborm
)
