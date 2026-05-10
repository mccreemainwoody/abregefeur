cmake_minimum_required(VERSION 3.25)

add_library(abregefeur_handlers STATIC)

target_include_directories(abregefeur_handlers
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/detail
)

add_subdirectory(artifact_generator)
add_subdirectory(note_recorder)
