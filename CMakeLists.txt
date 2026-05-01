cmake_minimum_required(VERSION 3.16)

project(abregefeur VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 6.10 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)
qt_policy(SET QTP0005 NEW)

add_subdirectory(src)
