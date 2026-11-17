# Qt Script for Applications (QSA) for Qt 5 and Qt 6

This venture tries to revive the corpse of QSA or Qt Script for Applications in a way so that is compiles against the Qt 5.15 and Qt 6.x series. QSA is a scripting framework initially created for Qt 3 that not only containes an ECMAScript interpreter but also an IDE. Unfortunately QSA was shelfed and the superseding projects did not offer the same level of features again.

## What has been achieved?

* Interpreter, associated utils, samples, the new editor and the workbench have been migrated over to Qt 5 and Qt 6
* Build system has been migrated to CMake, Qt 6 is preferred if both versions can be found (Qt 6 additionally needs the Core5Compat module)

## Building and using QSA

Configure and build with CMake 3.16 or newer, point `CMAKE_PREFIX_PATH` to the Qt installation to use. Installing QSA into the Qt installation (`CMAKE_INSTALL_PREFIX`) or any directory on `CMAKE_PREFIX_PATH` makes it available to other projects, this replaces the former `CONFIG += qsa` of qmake:

```cmake
find_package(qsa REQUIRED)
target_link_libraries(myapp PRIVATE qsa::qsa)
```

QSA has to be used with the same Qt major version it was built with.

## What is still left to do?

* Migrate the Q3TextEdit based editor to Qt 5 by integrating a bare minimum set of classes from the Qt 4.6 Qt 3 support layer
* Migrate and cleanup non Windows operating system specific code paths
* Fix the documentation build
