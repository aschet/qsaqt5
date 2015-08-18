TEMPLATE = app
SOURCES	+= main.cpp console.cpp
HEADERS += console.h
unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

!noeditor: FORMS = console.ui


# Leave away .. in your own code. See comment in ../qsa.prf.
load( ../qsa )

CONFIG += uic

#The following line was inserted by qt3to4
!neweditor: QT +=  qt3support 
