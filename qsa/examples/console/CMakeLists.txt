project(console)

set(UIS console.ui)

set(HEADERS_MOC console.h)

set(SOURCES console.cpp
	main.cpp	
)

qt_wrap_ui(HEADERS_UIS ${UIS})
qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(console ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(console Qt::Widgets qsa)
