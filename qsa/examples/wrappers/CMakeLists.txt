project(wrappers)

set(HEADERS_MOC wrappers.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES wrappers.cpp)

add_executable(wrappers ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(wrappers Qt5::Widgets qsa)
