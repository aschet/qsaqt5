project(scriptbutton)

set(HEADERS_MOC scriptbutton.h
	widgetwrapper.h
)

set(SOURCES scriptbutton.cpp
	widgetwrapper.cpp
	main.cpp
)

if(USE_QT6)
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(scriptbutton ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scriptbutton Qt${QT_VERSION_MAJOR}::Widgets qsa)

