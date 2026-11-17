project(spreadsheet)

add_executable(spreadsheet
	addscriptdialog.cpp
	addscriptdialog.h
	addscriptdialog.ui
	main.cpp
	sheetinterface.cpp
	sheetinterface.h
	spreadsheet.cpp
	spreadsheet.h
	spreadsheet.qrc
	spreadsheet.ui
)
target_link_libraries(spreadsheet PRIVATE qsa)

file(COPY euro.qs DESTINATION .)
file(COPY images DESTINATION .)
file(COPY math.qs DESTINATION .)
file(COPY spreadsheet.qsa DESTINATION .)

