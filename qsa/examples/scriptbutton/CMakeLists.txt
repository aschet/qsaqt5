project(scriptbutton)

set(HEADERS_MOC scriptbutton.h
	widgetwrapper.h
)

set(SOURCES scriptbutton.cpp
	widgetwrapper.cpp
	main.cpp
)

qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(scriptbutton ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scriptbutton Qt::Widgets qsa)
