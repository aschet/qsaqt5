include(GNUInstallDirs)

configure_file(qsa/qsconfig.h.in "${CMAKE_CURRENT_BINARY_DIR}/qsa/qsconfig.h")

set(QSA_HEADERS
	engine/qsclass.h
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
	engine/qsengine.h
	engine/qstimeouttrigger.h
	kernel/quickenv.h
	kernel/quickclassparser.h
	kernel/quickbytearrayobject.h
	kernel/quickcoordobjects.h
	kernel/qsmetaobject.h
	kernel/qsslot.h
	kernel/qsaqtcompat.h
	kernel/quickdebugger.h
	kernel/quickdispatchobject.h
	kernel/quickobjects.h
	kernel/quickinterpreter.h
	kernel/quickpixmapobject.h
	kernel/quickcolorobject.h
	kernel/quickfontobject.h
	qsa/qsaglobal.h
	qsa/qsobjectfactory.h
	qsa/qswrapperfactory.h
	qsa/qsutilfactory.h
	qsa/qsutilfactory_p.h
	qsa/qsinputdialogfactory.h
	qsa/qsinputdialogfactory_p.h
	qsa/qsinterpreter.h
	qsa/qsscript.h
	qsa/qsproject.h
)

# public headers that get installed, qsconfig.h is added below because it is generated
set(QSA_HEADERS_DIST
	qsa/qsaglobal.h
	qsa/qsinputdialogfactory.h
	qsa/qsinterpreter.h
	qsa/qsobjectfactory.h
	qsa/qsproject.h
	qsa/qsscript.h
	qsa/qsutilfactory.h
	qsa/qswrapperfactory.h
)

set(QSA_SOURCES
	engine/qsclass.cpp
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

set(QSA_PRIVATE_INCLUDE_DIRS engine kernel)
set(QSA_PUBLIC_INCLUDE_DIRS qsa)
set(QSA_QT_LIBS Qt::Widgets)

if(NOT QSA_NO_EDITOR)

list(APPEND QSA_HEADERS
	qsa/qseditor.h
	ide/conf.h
)
list(APPEND QSA_HEADERS_DIST
	qsa/qseditor.h
)
list(APPEND QSA_SOURCES
	qsa/qseditor.cpp
	ide/conf.cpp
)

if(QSA_NEW_EDITOR)

list(APPEND QSA_PRIVATE_INCLUDE_DIRS neweditor)
list(APPEND QSA_HEADERS
	neweditor/completionbox.h
	neweditor/linenumberwidget.h
	neweditor/parenmatcher.h
	neweditor/qsaeditor.h
	neweditor/qsaeditorinterface.h
	neweditor/blockdata.h
	neweditor/qsasyntaxhighlighter.h
)
list(APPEND QSA_SOURCES
	neweditor/completionbox.cpp
	neweditor/linenumberwidget.cpp
	neweditor/parenmatcher.cpp
	neweditor/qsaeditor.cpp
	neweditor/qsaeditorinterface.cpp
	neweditor/qsasyntaxhighlighter.cpp
	neweditor/yyindent.cpp
)

else()

if(Qt6_FOUND)
	message(FATAL_ERROR "The Q3TextEdit based editor requires Qt 5, enable QSA_NEW_EDITOR when building against Qt 6.")
endif()

list(APPEND QSA_PRIVATE_INCLUDE_DIRS editor ../tools/designer/editor Qt3Support)
list(APPEND QSA_HEADERS
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
	../tools/designer/editor/cindent.h
	../tools/designer/editor/paragdata.h
	../tools/designer/editor/parenmatcher.h
)
list(APPEND QSA_SOURCES
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

endif()

if(NOT QSA_NO_IDE)

list(APPEND QSA_QT_LIBS Qt::PrintSupport)
list(APPEND QSA_PUBLIC_INCLUDE_DIRS ide)
list(APPEND QSA_HEADERS_DIST
	ide/qsworkbench.h
)
list(APPEND QSA_HEADERS
	ide/idewindow.h
	ide/preferences.h
	ide/qsworkbench.h
)
list(APPEND QSA_SOURCES
	ide/idewindow.cpp
	ide/preferences.cpp
	ide/qsworkbench.cpp
	ide/findtext.ui
	ide/gotoline.ui
	ide/idewindow.ui
	ide/outputcontainer.ui
	ide/preferences.ui
	ide/preferencescontainer.ui
	ide/projectcontainer.ui
	ide/replacetext.ui
	ide/variablescontainer.ui
	ide/ide.qrc
)

endif()

endif()

if(QSA_NO_DLL)
	set(QSA_LIB_MODE STATIC)
else()
	set(QSA_LIB_MODE SHARED)
endif()

add_library(qsa ${QSA_LIB_MODE} ${QSA_SOURCES} ${QSA_HEADERS})
add_library(qsa::qsa ALIAS qsa)

# the file only contains Q_OBJECT inside a documentation sample
set_source_files_properties(qsa/qswrapperfactory.cpp PROPERTIES SKIP_AUTOMOC ON)

list(TRANSFORM QSA_PRIVATE_INCLUDE_DIRS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

target_include_directories(qsa
	PRIVATE
		${QSA_PRIVATE_INCLUDE_DIRS}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/qsa>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
foreach(dir IN LISTS QSA_PUBLIC_INCLUDE_DIRS)
	target_include_directories(qsa PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dir}>")
endforeach()

target_compile_definitions(qsa PRIVATE HAVE_CONFIG_H QSDEBUGGER)
if(NOT QSA_NO_DLL)
	# exports the symbols, consumers must not define it
	target_compile_definitions(qsa PRIVATE QSA_DLL)
endif()
if(Qt5_FOUND)
	target_compile_definitions(qsa PUBLIC QT_DISABLE_DEPRECATED_BEFORE=0x050F00)
endif()
if(MSVC)
	target_compile_definitions(qsa PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
	set_target_properties(qsa PROPERTIES DEBUG_POSTFIX d)
endif()

target_link_libraries(qsa PUBLIC ${QSA_QT_LIBS})

install(FILES ${QSA_HEADERS_DIST} "${CMAKE_CURRENT_BINARY_DIR}/qsa/qsconfig.h"
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS qsa EXPORT qsaTargets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# CMake package, replaces the qmake feature file (CONFIG += qsa). Installing into the
# prefix of Qt makes find_package(qsa) work without any further setup.
include(CMakePackageConfigHelpers)

if(Qt6_FOUND)
	set(QSA_QT_MAJOR 6)
else()
	set(QSA_QT_MAJOR 5)
endif()
set(QSA_PACKAGE_QT_COMPONENTS ${QSA_QT_COMPONENTS})
string(REPLACE ";" " " QSA_PACKAGE_QT_COMPONENTS "${QSA_PACKAGE_QT_COMPONENTS}")

set(QSA_CMAKE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/qsa)

configure_package_config_file(qsaConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/qsaConfig.cmake"
	INSTALL_DESTINATION ${QSA_CMAKE_INSTALL_DIR})
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/qsaConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(EXPORT qsaTargets
	NAMESPACE qsa::
	DESTINATION ${QSA_CMAKE_INSTALL_DIR})
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/qsaConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/qsaConfigVersion.cmake"
	DESTINATION ${QSA_CMAKE_INSTALL_DIR})
