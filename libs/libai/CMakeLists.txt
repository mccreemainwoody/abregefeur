cmake_minimum_required(VERSION 3.25)

option(LIBAI_USE_STATIC_LIBS "Build libai as a static library" OFF)

set(LIBAI_LIBRARY_VERSION 0.1.0)
set(LIBAI_LIBRARY_VERSION_MAJOR 0)

include(GNUInstallDirs)

find_package(CURL 8.19.0 REQUIRED COMPONENTS HTTPS)
find_package(nlohmann_json 3.12.0 REQUIRED)

if (LIBAI_USE_STATIC_LIBS)
    add_library(libai STATIC)
else()
    add_library(libai SHARED)
endif()

set_target_properties(libai PROPERTIES
    LIBRARY_OUTPUT_NAME ai
    VERSION ${LIBAI_LIBRARY_VERSION}
    SOVERSION ${LIBAI_LIBRARY_VERSION_MAJOR}
)

target_include_directories(libai
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        detail/
)

add_subdirectory(src)

install(TARGETS libai
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
