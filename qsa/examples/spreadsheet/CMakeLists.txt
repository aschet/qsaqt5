project(spreadsheet)

set(UIS addscriptdialog.ui
	spreadsheet.ui	
)

set(HEADERS_MOC addscriptdialog.h
	sheetinterface.h
	spreadsheet.h
)

set(SOURCES addscriptdialog.cpp
	main.cpp
	sheetinterface.cpp
	spreadsheet.cpp	
)

if(USE_QT6)
    qt6_add_resources(SOURCES_QRC spreadsheet.qrc)
    qt6_wrap_ui(HEADERS_UIS ${UIS})
    qt6_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
else()
    qt5_add_resources(SOURCES_QRC spreadsheet.qrc)
    qt5_wrap_ui(HEADERS_UIS ${UIS})
    qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})
endif()

add_executable(spreadsheet ${SOURCES_QRC} ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(spreadsheet Qt${QT_VERSION_MAJOR}::Widgets qsa)

file(COPY euro.qs DESTINATION .)
file(COPY images DESTINATION .)
file(COPY math.qs DESTINATION .)
file(COPY spreadsheet.qsa DESTINATION .)

