cmake_minimum_required(VERSION 3.25)

project(abregefeur VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Quick Sql)

qt_standard_project_setup(REQUIRES 6.10)
qt_policy(SET QTP0005 NEW)

add_subdirectory(src)
