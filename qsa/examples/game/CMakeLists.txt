project(game)

set(UIS gamewindow.ui)

qt5_wrap_ui(HEADERS_UIS ${UIS})

set(HEADERS_MOC gamewindow.h
	playfield.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES gamewindow.cpp
	main.cpp
	playfield.cpp
)

add_executable(game ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(game Qt5::Widgets qsa)
