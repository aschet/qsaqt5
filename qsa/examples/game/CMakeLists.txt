project(game)

set(UIS gamewindow.ui)

set(HEADERS_MOC gamewindow.h
	playfield.h)

set(SOURCES gamewindow.cpp
	main.cpp
	playfield.cpp
)

if(USE_QT6)
    qt6_wrap_ui(HEADERS_UIS ${UIS})
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_ui(HEADERS_UIS ${UIS})
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(game ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(game Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY background.png DESTINATION .)
file(COPY ball.png DESTINATION .)
file(COPY bouncer.qs DESTINATION .)
file(COPY brick1.png DESTINATION .)
file(COPY brick2.png DESTINATION .)
file(COPY brick3.png DESTINATION .)
file(COPY bullet.png DESTINATION .)
file(COPY enemy.png DESTINATION .)
file(COPY plate.png DESTINATION .)
file(COPY player.png DESTINATION .)
file(COPY shooter.qs DESTINATION .)
