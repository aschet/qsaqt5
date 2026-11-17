project(scriptbutton)

add_executable(scriptbutton
	main.cpp
	scriptbutton.cpp
	scriptbutton.h
	widgetwrapper.cpp
	widgetwrapper.h
)
target_link_libraries(scriptbutton PRIVATE qsa)
