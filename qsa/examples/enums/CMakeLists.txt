project(enums)

set(HEADERS_MOC main.h)

set(SOURCES main.cpp)

qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(enums ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(enums Qt::Widgets qsa)

file(COPY enums.qsa DESTINATION .)
file(COPY main.qs DESTINATION .)
