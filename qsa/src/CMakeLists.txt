cmake_minimum_required(VERSION 3.3.1)

project(src)

# QSA_NO_DLL
option(QSA_NO_EDITOR "Does not compile QSA Workbench or QSA editor into QSA." OFF)
option(QSA_NEW_EDITOR "Does compile QTextEdit instead of Q3TextEdit based editor into QSA." ON)
option(QSA_NO_IDE "Does not compile QSA Workbench into QSA." OFF)

# Qt specific setup

#	win32:DEFINES	+= QSA_DLL
#} else {
#	win32:DEFINES   += QSA_NO_DLL

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

# QSA
add_definitions(-DHAVE_CONFIG_H -DQSDEBUGGER -DQSA_DLL -DQSA_NO_EDITOR)
#include_directories(editor engine ide kernel neweditor qsa)
include_directories(engine kernel qsa)

set(HEADERS_MOC
	engine/qsengine.h
	engine/qstimeouttrigger.h
	kernel/quickdebugger.h
	kernel/quickdispatchobject.h
	kernel/quickobjects.h
	kernel/quickinterpreter.h
	qsa/qsinterpreter.h
	qsa/qsscript.h
	qsa/qsproject.h
	qsa/qsutilfactory_p.h
	qsa/qsinputdialogfactory_p.h
)

qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

set(HEADERS engine/qsclass.h
	engine/qsglobal.h
	engine/qsmember.h
	engine/qstypes.h
	engine/qsenv.h
	engine/qserrors.h
	engine/qsnodes.h
	engine/qslexer.h
	engine/grammar.h
	engine/qsoperations.h
	engine/qscheck.h
	engine/qsobject.h
	engine/qsreference.h
	engine/qsfunction.h
	engine/qslookup.h
	engine/qsinternal.h
	engine/qsdebugger.h
	engine/qsmath_object.h
	engine/qsbool_object.h
	engine/qsobject_object.h
	engine/qserror_object.h
	engine/qsarray_object.h
	engine/qsnumber_object.h
	engine/qsdate_object.h
	engine/qsregexp_object.h
	engine/qsfuncref.h
	engine/qsobjectlist.h
	engine/qsclasslist.h
	engine/qsnumeric.h
	kernel/quickenv.h
	kernel/quickclassparser.h
	kernel/quickbytearrayobject.h
	kernel/quickcoordobjects.h
	kernel/qsmetaobject.h
	kernel/qsslot.h
	kernel/quickpixmapobject.h
	kernel/quickcolorobject.h
	kernel/quickfontobject.h
	qsa/qsobjectfactory.h
	qsa/qswrapperfactory.h
	qsa/qsutilfactory.h
	qsa/qsinputdialogfactory.h
)

set(SOURCES engine/qsclass.cpp
	engine/qsmember.cpp
	engine/qstypes.cpp
	engine/qsenv.cpp
	engine/qslexer.cpp
	engine/grammar.cpp
	engine/qsnodes.cpp
	engine/qsoperations.cpp
	engine/qscheck.cpp
	engine/qsengine.cpp 
	engine/qsobject.cpp
	engine/qsfunction.cpp
	engine/qslookup.cpp
	engine/qsinternal.cpp
	engine/qsdebugger.cpp
	engine/qsglobal_object.cpp
	engine/qsmath_object.cpp
	engine/qsbool_object.cpp
	engine/qsobject_object.cpp
	engine/qserror_object.cpp
	engine/qsarray_object.cpp
	engine/qsstring_object.cpp
	engine/qsnumber_object.cpp
	engine/qsdate_object.cpp
	engine/qsregexp_object.cpp
	engine/qsfuncref.cpp
	kernel/quickinterpreter.cpp
	kernel/quickdebugger.cpp
	kernel/quickobjects.cpp
	kernel/quickenv.cpp
	kernel/quickclassparser.cpp
	kernel/quickbytearrayobject.cpp
	kernel/quickcoordobjects.cpp
	kernel/quickdispatchobject.cpp
	kernel/qsmetaobject.cpp
	kernel/quickpixmapobject.cpp
	kernel/quickcolorobject.cpp
	kernel/quickfontobject.cpp
	qsa/qsproject.cpp
	qsa/qsinterpreter.cpp
	qsa/qsobjectfactory.cpp
	qsa/qswrapperfactory.cpp
	qsa/qsscript.cpp
	qsa/qsutilfactory.cpp
	qsa/qsinputdialogfactory.cpp
)

add_library(qsa SHARED ${SOURCES} ${SOURCES_MOC} ${HEADERS} ${HEADERS_MOC})
target_link_libraries(qsa Qt5::Widgets)

#!noeditor|neweditor{
#!noeditor{
#	SOURCES += qseditor.cpp
#	HEADERS += qseditor.h
#}
