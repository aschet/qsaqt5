cmake_minimum_required(VERSION 3.16.0)

project(qsa)

option(USE_QT6 "Enable this if you want to use Qt6, instead of Qt5" no)

if(USE_QT6)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
else()
    find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)
