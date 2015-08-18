#The following line was commented out by qt3to4
#REQUIRES = table
SOURCES	+= main.cpp sheetinterface.cpp addscriptdialog.cpp spreadsheet.cpp
HEADERS	+= sheetinterface.h addscriptdialog.h spreadsheet.h

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
FORMS	= spreadsheet.ui addscriptdialog.ui 
RESOURCES += spreadsheet.qrc
TEMPLATE	=app

# Leave away .. in your own code. See comment in ../qsa.prf.
load( ../qsa )

