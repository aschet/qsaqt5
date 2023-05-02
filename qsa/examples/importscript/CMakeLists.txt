project(importscript)

set(HEADERS_MOC main.h)

set(SOURCES main.cpp)

qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(importscript ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(importscript Qt::Widgets qsa)

file(COPY functions.qs DESTINATION .)
