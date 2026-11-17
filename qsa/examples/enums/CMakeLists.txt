project(enums)

add_executable(enums
	main.cpp
	main.h
)
target_link_libraries(enums PRIVATE qsa)

file(COPY enums.qsa DESTINATION .)
file(COPY main.qs DESTINATION .)
