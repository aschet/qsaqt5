project(scribblescripter)

add_executable(scribblescripter
	main.cpp
	scribblescripter.cpp
	scribblescripter.h
)
target_link_libraries(scribblescripter PRIVATE qsa)

file(COPY scribble.qs DESTINATION .)
file(COPY scribblescript.qsa DESTINATION .)
