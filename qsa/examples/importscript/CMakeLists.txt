project(importscript)

set(HEADERS_MOC main.h)

set(SOURCES main.cpp)

if(USE_QT6)
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(importscript ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(importscript Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY functions.qs DESTINATION .)
