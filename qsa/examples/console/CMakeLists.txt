project(console)

set(UIS console.ui)

set(HEADERS_MOC console.h)

set(SOURCES console.cpp
	main.cpp	
)

if(USE_QT6)
    qt6_wrap_ui(HEADERS_UIS ${UIS})
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_wrap_ui(HEADERS_UIS ${UIS})
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(console ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(console Qt${QT_VERSION_MAJOR}::Widgets qsa)
