cmake_minimum_required(VERSION 2.8.12.2)

project(src)

if (MSVC)
	set(CMAKE_DEBUG_POSTFIX "d")
endif()

option(QSA_NO_DLL "Does not compile as shared library." OFF)
option(QSA_NO_EDITOR "Does not compile QSA Workbench or QSA editor into QSA." OFF)
option(QSA_NEW_EDITOR "Does compile QTextEdit instead of Q3TextEdit based editor into QSA." ON)
option(QSA_NO_IDE "Does not compile QSA Workbench into QSA." OFF)

if(${QSA_NO_DLL})
set(LIB_MODE STATIC)
else()
set(LIB_MODE SHARED)
add_definitions(-DQSA_DLL)
endif(${QSA_NO_DLL})

configure_file(qsa/qsconfig.h.in "${CMAKE_CURRENT_SOURCE_DIR}/qsa/qsconfig.h")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

include_directories(engine kernel qsa)
add_definitions(-DHAVE_CONFIG_H -DQSDEBUGGER)

set(UIS "")

set(QRCS "")

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
	qsa/qsaglobal.h
	qsa/qsconfig.h
	qsa/qsobjectfactory.h
	qsa/qswrapperfactory.h
	qsa/qsutilfactory.h
	qsa/qsinputdialogfactory.h
)

set(HEADERS_DIST qsa/qsaglobal.h
	qsa/qsconfig.h
	qsa/qsinputdialogfactory.h
	qsa/qsinterpreter.h
	qsa/qsobjectfactory.h
	qsa/qsproject.h
	qsa/qsscript.h
	qsa/qsutilfactory.h
	qsa/qswrapperfactory.h
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

set (QT_LIBS Qt5::Widgets)

if(NOT ${QSA_NO_EDITOR})

set(HEADERS_MOC ${HEADERS_MOC}
	qsa/qseditor.h
)
set(HEADERS ${HEADERS}
	ide/conf.h
)
set(HEADERS_DIST ${HEADERS_DIST}
	qsa/qseditor.h
)
set(SOURCES ${SOURCES}
	qsa/qseditor.cpp
	ide/conf.cpp
)

if(${QSA_NEW_EDITOR})

include_directories(neweditor)
set(HEADERS_MOC ${HEADERS_MOC}
	neweditor/completionbox.h	
	neweditor/linenumberwidget.h
	neweditor/parenmatcher.h
	neweditor/qsaeditor.h
	neweditor/qsaeditorinterface.h
)
set(HEADERS ${HEADERS}
	neweditor/blockdata.h
	neweditor/qsasyntaxhighlighter.h
)
set(SOURCES ${SOURCES}
	neweditor/completionbox.cpp
	neweditor/linenumberwidget.cpp
	neweditor/parenmatcher.cpp
	neweditor/qsaeditor.cpp
	neweditor/qsaeditorinterface.cpp
	neweditor/qsasyntaxhighlighter.cpp
	neweditor/yyindent.cpp
)

else()

include_directories(editor ../tools/designer/editor Qt3Support)
set(UIS ${UIS}
#	../tools/designer/editor/preferences.ui
#	../tools/designer/editor/preferences.ui.h
)
set(HEADERS_MOC ${HEADERS_MOC}
	editor/qsabrowser.h
	editor/qsacompletion.h
	editor/qsaeditor.h
	editor/qsaeditorinterface.h
	../tools/designer/editor/arghintwidget.h
	../tools/designer/editor/browser.h
	../tools/designer/editor/completion.h
	../tools/designer/editor/editor.h
	../tools/designer/editor/markerwidget.h
	../tools/designer/editor/viewmanager.h
)
set(HEADERS ${HEADERS}
	../tools/designer/editor/cindent.h
	../tools/designer/editor/paragdata.h
	../tools/designer/editor/parenmatcher.h
)
set(SOURCES ${SOURCES}
	editor/qsabrowser.cpp
	editor/qsacompletion.cpp
	editor/qsaeditor.cpp
	editor/qsaeditorinterface.cpp
	../tools/designer/editor/arghintwidget.cpp
	../tools/designer/editor/browser.cpp
	../tools/designer/editor/cindent.cpp
	../tools/designer/editor/completion.cpp
	../tools/designer/editor/editor.cpp
	../tools/designer/editor/markerwidget.cpp
	../tools/designer/editor/parenmatcher.cpp
	../tools/designer/editor/viewmanager.cpp
	../tools/designer/editor/yyindent.cpp
)

endif(${QSA_NEW_EDITOR})

if(NOT ${QSA_NO_IDE})

set(HEADERS_DIST ${HEADERS_DIST}
	ide/qsworkbench.h
)

find_package(Qt5PrintSupport REQUIRED)
include_directories(${Qt5PrintSupport_INCLUDE_DIRS})
add_definitions(${Qt5PrintSupport_DEFINITIONS})
set(QT_LIBS ${QT_LIBS}
	Qt5::PrintSupport
)

include_directories(ide)
set(UIS ${UIS}
	ide/findtext.ui 
	ide/gotoline.ui
	ide/idewindow.ui
	ide/outputcontainer.ui
	ide/preferences.ui
	ide/preferencescontainer.ui
	ide/projectcontainer.ui
	ide/replacetext.ui
	ide/variablescontainer.ui
)
set(QRCS ${QRCS}
	ide/ide.qrc
)
set(HEADERS_MOC ${HEADERS_MOC}
	ide/idewindow.h
	ide/preferences.h
	ide/qsworkbench.h	
)
set(SOURCES ${SOURCES}
	ide/idewindow.cpp
	ide/preferences.cpp
	ide/qsworkbench.cpp
	ide/idewindow.cpp
	ide/idewindow.cpp	
)

endif(NOT ${QSA_NO_IDE})

endif(NOT ${QSA_NO_EDITOR})

qt5_add_resources(SOURCES_QRC ${QRCS})
qt5_wrap_ui(HEADERS_UIS ${UIS})
qt5_wrap_cpp(SOURCES_MOC ${HEADERS_MOC})

add_library(qsa ${LIB_MODE} ${SOURCES} ${SOURCES_MOC} ${SOURCES_QRC} ${HEADERS} ${HEADERS_MOC} ${HEADERS_UIS})
if (MSVC)
	set_target_properties(qsa PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif()
target_link_libraries(qsa ${QT_LIBS})

install(FILES ${HEADERS_DIST} DESTINATION include)

install(TARGETS qsa
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)