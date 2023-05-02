cmake_minimum_required(VERSION 3.16.0)

project(qsa)

find_package(Qt6 COMPONENTS Widgets Core5Compat)
if (NOT Qt6_FOUND)
    add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets)
endif()

add_subdirectory(src)
add_subdirectory(examples)
