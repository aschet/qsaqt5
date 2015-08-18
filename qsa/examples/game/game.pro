TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += playfield.h gamewindow.h
FORMS += gamewindow.ui
SOURCES += main.cpp playfield.cpp gamewindow.cpp

# Leave away .. in your own code. See comment in ../qsa.prf.
load( ../qsa )


