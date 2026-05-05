cmake_minimum_required(VERSION 3.25)

target_sources(liborm
    PRIVATE
        database.cpp
        entity.cpp
)

target_link_libraries(liborm
    PRIVATE
        Qt6::Core
        Qt6::Sql
)
