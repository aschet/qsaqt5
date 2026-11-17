project(filter)

add_executable(filter
	data.cpp
	data.h
	main.cpp
	modulefactory.cpp
	modulefactory.h
	modules.cpp
	modules.h
)
target_link_libraries(filter PRIVATE qsa)

file(COPY bump.png DESTINATION .)
file(COPY filter.qsa DESTINATION .)
file(COPY main.qs DESTINATION .)
