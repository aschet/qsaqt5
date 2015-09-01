project(enums)

set(HEADERS_MOC main.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES main.cpp)

add_executable(enums ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(enums Qt5::Widgets qsa)
