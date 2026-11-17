project(importscript)

add_executable(importscript
	main.cpp
	main.h
)
target_link_libraries(importscript PRIVATE qsa)

file(COPY functions.qs DESTINATION .)
