cmake_minimum_required(VERSION 3.16)

project(qsa VERSION 1.2.3 LANGUAGES CXX)

option(QSA_NO_DLL "Does not compile as shared library." OFF)
option(QSA_NO_EDITOR "Does not compile QSA Workbench or QSA editor into QSA." OFF)
option(QSA_NEW_EDITOR "Does compile QTextEdit instead of Q3TextEdit based editor into QSA." ON)
option(QSA_NO_IDE "Does not compile QSA Workbench into QSA." OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QSA_QT_COMPONENTS Widgets)
if(NOT QSA_NO_EDITOR AND NOT QSA_NO_IDE)
    list(APPEND QSA_QT_COMPONENTS PrintSupport)
endif()

# Qt 6 is preferred, Qt 5.15 is the oldest supported version
find_package(Qt6 QUIET COMPONENTS ${QSA_QT_COMPONENTS} Core5Compat)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS ${QSA_QT_COMPONENTS})
endif()

add_subdirectory(src)
add_subdirectory(examples)
