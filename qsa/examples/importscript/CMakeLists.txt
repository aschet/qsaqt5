project(importscript)

set(HEADERS_MOC main.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES main.cpp)

add_executable(importscript ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(importscript Qt5::Widgets qsa)

file(COPY functions.qs DESTINATION .)
