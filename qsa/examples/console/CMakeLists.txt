project(console)

add_executable(console
	console.cpp
	console.h
	console.ui
	main.cpp
)
target_link_libraries(console PRIVATE qsa)
