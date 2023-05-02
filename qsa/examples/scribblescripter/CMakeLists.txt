project(scribblescripter)

set(HEADERS_MOC scribblescripter.h)

set(SOURCES scribblescripter.cpp
	main.cpp	
)

qt_wrap_ui(HEADERS_UIS ${UIS})
qt_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_executable(scribblescripter ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scribblescripter Qt::Widgets qsa)

file(COPY scribble.qs DESTINATION .)
file(COPY scribblescript.qsa DESTINATION .)
