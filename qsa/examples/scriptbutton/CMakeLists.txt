project(scriptbutton)

set(HEADERS_MOC scriptbutton.h
	widgetwrapper.h
)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES scriptbutton.cpp
	widgetwrapper.cpp
	main.cpp
)

add_executable(scriptbutton ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scriptbutton Qt5::Widgets qsa)

