project(scribblescripter)

qt5_wrap_ui(HEADERS_UIS ${UIS})

set(HEADERS_MOC scribblescripter.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES scribblescripter.cpp
	main.cpp	
)

add_executable(scribblescripter ${SOURCES} ${SOURCES_MOC} ${HEADERS_MOC})
target_link_libraries(scribblescripter Qt5::Widgets qsa)

