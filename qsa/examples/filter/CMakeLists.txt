project(filter)

set(HEADERS_MOC modules.h)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(HEADERS data.h
	modulefactory.h
)

set(SOURCES data.cpp
	main.cpp
	modulefactory.cpp
	modules.cpp
)

add_executable(filter ${SOURCES} ${SOURCES_MOC} ${HEADERS} ${HEADERS_MOC})
target_link_libraries(filter Qt5::Widgets qsa)

file(COPY bump.png DESTINATION .)
file(COPY filter.qsa DESTINATION .)
file(COPY main.qs DESTINATION .)
