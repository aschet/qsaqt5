project(spreadsheet)

qt5_add_resources(SOURCES_QRC spreadsheet.qrc)

set(UIS addscriptdialog.ui
	spreadsheet.ui	
)

qt5_wrap_ui(HEADERS_UIS ${UIS})

set(HEADERS_MOC addscriptdialog.h
	sheetinterface.h
	spreadsheet.h
)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(SOURCES addscriptdialog.cpp
	main.cpp
	sheetinterface.cpp
	spreadsheet.cpp	
)

add_executable(spreadsheet ${SOURCES_QRC} ${SOURCES} ${SOURCES_MOC} ${HEADERS_UIS} ${HEADERS_MOC})
target_link_libraries(spreadsheet Qt5::Widgets qsa)

file(COPY euro.qs DESTINATION .)
file(COPY images DESTINATION .)
file(COPY math.qs DESTINATION .)
file(COPY spreadsheet.qsa DESTINATION .)

