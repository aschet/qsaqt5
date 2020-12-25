project(scribblescripter)

set(HEADERS_MOC scribblescripter.h)

set(SOURCES scribblescripter.cpp
	main.cpp	
)

if(USE_QT6)
    qt6_wrap_ui(HEADERS_UIS ${UIS})
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_ui(HEADERS_UIS ${UIS})
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(scribblescripter ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scribblescripter Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY scribble.qs DESTINATION .)
file(COPY scribblescript.qsa DESTINATION .)
