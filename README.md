# Qt Script for Applications (QSA) for Qt 5

This venture tries to revive the corpse of QSA or Qt Script for Applications in a way so that is compiles against the Qt 5.x series. QSA is a scripting framework initially created for Qt 3 that not only containes an ECMAScript interpreter but also an IDE. Unfortunately QSA was shelfed and the superseding projects did not offer the same level of features again.

## What has been achieved?

* Interpreter, associated utils, samples, the new editor and the workbench have been migrated over to Qt 5
* Building via QMake on Windows is possible although only with a fixed configuration (ide+neweditor)

## What is still left to do?

* Migrate the Q3TextEdit based editor to Qt 5 by integrating a bare minimum set of classes from the Qt 4.6 Qt 3 support layer
* Migrate and cleanup non Windows operating system specific code paths
* Fix the build system: the configuration script has to be replaced with a working solution, QMake project files have to be adjusted that all configuration options will work
* Fix the documentation build
* Fix the sample build
