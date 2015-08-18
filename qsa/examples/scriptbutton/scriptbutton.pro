SOURCES = main.cpp

!noeditor {
  SOURCES += scriptbutton.cpp widgetwrapper.cpp
  HEADERS += scriptbutton.h widgetwrapper.h
}

# Leave away .. in your own code. See comment in ../qsa.prf.
load( ../qsa )
