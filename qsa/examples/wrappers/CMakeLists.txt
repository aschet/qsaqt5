project(wrappers)

add_executable(wrappers
	wrappers.cpp
	wrappers.h
)
target_link_libraries(wrappers PRIVATE qsa)

file(COPY click.qs DESTINATION .)
file(COPY test.qs DESTINATION .)
