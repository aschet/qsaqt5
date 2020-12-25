project(enums)

set(HEADERS_MOC main.h)

set(SOURCES main.cpp)

if(USE_QT6)
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()


add_executable(enums ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(enums Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY enums.qsa DESTINATION .)
file(COPY main.qs DESTINATION .)
