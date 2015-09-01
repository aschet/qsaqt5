project(examples)

include_directories(../src/qsa)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(console)
add_subdirectory(enums)
add_subdirectory(filter)
add_subdirectory(game)
add_subdirectory(importscript)
add_subdirectory(scribblescripter)
add_subdirectory(scriptbutton)
add_subdirectory(spreadsheet)
add_subdirectory(wrappers)
