project(wrappers)

set(HEADERS_MOC wrappers.h)

set(SOURCES wrappers.cpp)

qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(wrappers ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(wrappers Qt::Widgets qsa)

file(COPY click.qs DESTINATION .)
file(COPY test.qs DESTINATION .)
