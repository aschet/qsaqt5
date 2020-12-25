project(wrappers)

set(HEADERS_MOC wrappers.h)

set(SOURCES wrappers.cpp)

if(USE_QT6)
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()


add_executable(wrappers ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(wrappers Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY click.qs DESTINATION .)
file(COPY test.qs DESTINATION .)
