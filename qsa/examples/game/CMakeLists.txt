project(game)

add_executable(game
	gamewindow.cpp
	gamewindow.h
	gamewindow.ui
	main.cpp
	playfield.cpp
	playfield.h
)
target_link_libraries(game PRIVATE qsa)
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

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
