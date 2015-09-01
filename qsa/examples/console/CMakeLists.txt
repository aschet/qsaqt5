project(console)

set(FORMS console.ui)

qt5_wrap_ui(HEADERS_FORMS ${FORMS})

set(HEADERS_MOC console.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES console.cpp
	main.cpp	
)

add_executable(console ${SOURCES} ${SOURCES_MOC} ${HEADERS_FORMS} ${HEADERS_MOC})
target_link_libraries(console Qt5::Widgets)
