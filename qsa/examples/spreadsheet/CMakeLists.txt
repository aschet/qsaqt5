project(spreadsheet)

qt5_add_resources(SOURCES_QRC spreadsheet.qrc)

set(FORMS addscriptdialog.ui
	spreadsheet.ui	
)

qt5_wrap_ui(HEADERS_FORMS ${FORMS})

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

add_executable(spreadsheet ${SOURCES_QRC} ${SOURCES} ${SOURCES_MOC} ${HEADERS_FORMS} ${HEADERS_MOC})
target_link_libraries(spreadsheet Qt5::Widgets qsa)
