/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech AS. All rights reserved.
**
** This file is part of the QSA of the Qt Toolkit.
**
** For QSA Commercial License Holders (non-open source):
** 
** Licensees holding a valid Qt Script for Applications (QSA) License Agreement
** may use this file in accordance with the rights, responsibilities and
** obligations contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of the Licensing Agreement are
** not clear to you.
** 
** Further information about QSA licensing is available at:
** http://www.trolltech.com/products/qsa/licensing.html or by contacting
** info@trolltech.com.
** 
** 
** For Open Source Edition:  
** 
** This file may be used under the terms of the GNU General Public License
** version 2 as published by the Free Software Foundation and appearing in the
** file LICENSE.GPL included in the packaging of this file.  Please review the
** following information to ensure GNU General Public Licensing requirements
** will be met:  http://www.trolltech.com/products/qt/opensource.html 
** 
** If you are unsure which license is appropriate for your use, please review
** the following information:
** http://www.trolltech.com/products/qsa/licensing.html or contact the 
** sales department at sales@trolltech.com.

**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

/*!
  \class QSUtilFactory qsutilfactory.h

  \brief The QSUtilFactory class extends QSA with classes to allow
  file access, directory traversal and executing external processes.

  To extend the interpreter with the Utililty Framework you must
  create an instance of the QSUtilFactory class and add it to the
  interpreter using the function QSInterpreter::addObjectFactory().
  For example:

  \code
  QSProject proj;
  QSInterpreter *ip = proj->interpreter();
  ip->addObjectFactory( new QSUtilFactory );
  \endcode

  The script extensions provided by the QSUtilFactory are
  described in detail in \l {QSA Utility Framework}
 */

/*!
  \enum QSUtilFactory::Utilities

  The Utilities enum can be used to enable and disable script access
  to the classes that the utility factory provides, thereby
  controlling the access that end users can have to the underlying
  system.

  \value None No classes are available. If no access is required then
  there is no point in adding the QSUtilFactory to the interpreter at
  all.

  \value File Gives access to the File class.

  \value Directory Gives access to the Directory class.

  \value Process Gives access to Process class.

  \value All Gives access to all the classes in availble in the
  factory. This is the default.

*/

/*!
  \fn QSUtilFactory::interpreter() const
  \overload
*/

#include "qsinterpreter.h"
#include "qsutilfactory.h"
#include "qsutilfactory_p.h"



/*! Instantiates the QSUtilFactory and enables the script classes
  specified in \a enableFlags. \a enableFlags is a bitmask of the
  \l Utilities enum.

  The QSUtilityFactory must be added to an interpreter before its
  classes can be used

  \sa QSInterpreter::addObjectFactory(), Utilities
*/
QSUtilFactory::QSUtilFactory(uint enableFlags)
{
    if ((enableFlags&File) != 0)
	registerClass(QString::fromLatin1("File"), &QSFile::staticMetaObject,
                      new QSFileStatic(this));
    if ((enableFlags&Directory) != 0)
	registerClass(QString::fromLatin1("Dir"), &QSDir::staticMetaObject,
                      new QSDirStatic(this));
    if ((enableFlags&Process) != 0) {
        registerClass(QString::fromLatin1("Process"), &QSProcess::staticMetaObject,
                      new QSProcessStatic(this));
    }
}

/*!
  \internal
*/
QObject *QSUtilFactory::create( const QString &name,
				const QVariantList &args,
				QObject * )
{
    int argCount = args.size();

    // File construction..
    if (name == QString::fromLatin1("File")) {
	if (argCount == 0) {
	    interpreter()->throwError(QString::fromLatin1("Cannot construct File, "
                                                          "missing argument filename"));
	    return 0;
	}
	QVariant fn = args[0];
	if (fn.type() != QVariant::String) {
	    interpreter()->throwError(QString::fromLatin1("Cannot construct File, "
                                                          "Filename must be of type string"));
	    return 0;
	}
	return new QSFile(qvariant_cast<QString>(args[0]), interpreter());
    }

    // Dir construction
    else if (name == QString::fromLatin1("Dir")) {
	if (argCount >= 1) {
	    QVariant fn = args[0];
	    if (fn.type() != QVariant::String) {
		interpreter()->throwError(QString::fromLatin1("Cannot construct Dir object, "
                                                              "Filename must be of type string"));
		return 0;
	    }
	    return new QSDir(qvariant_cast<QString>(args[0]), interpreter());
	} else {
	    return new QSDir(QDir::currentPath(), interpreter());
	}
    }

    else if (name == QString::fromLatin1("Process")) {
	if (argCount>=1) {
	    QStringList commands;
	    for (int i=0; i<argCount; ++i) {
		if (args[i].type() == QVariant::StringList)
		    commands += args[i].toStringList();
		else
		    commands += args[i].toString();
	    }
	    return new QSProcess(this, commands);
	} else {
	    return new QSProcess(this);
	}
    }

    else {
	interpreter()->throwError(QString::fromLatin1("QSUtilfactory::create(), don't know how to create: ")
				  + name);
	return 0;
    }
}

/********************************************************************************
 * class QSFileStatic
 */

void QSFileStatic::write(const QString &fileName, const QString &content)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
	factory->interpreter()->throwError(QString::fromLatin1("Could open file '") + fileName + QString::fromLatin1("' for writing"));
    else if (!file.write(content.toLocal8Bit()) == content.length())
	factory->interpreter()->throwError(QString::fromLatin1("Failed to write file"));
}

QString QSFileStatic::read(const QString &fileName)
{
    QFile file(fileName);
    if (!file.exists()) {
	factory->interpreter()->throwError(QString::fromLatin1("File '%1' does not exist").arg(fileName));
	return QString();
    } else if (!file.open(QIODevice::ReadOnly)) {
	factory->interpreter()->throwError(QString::fromLatin1("Could not read file '%1'").arg(fileName));
	return QString();
    }
    return QString::fromLocal8Bit(file.readAll());
}

void QSFileStatic::remove(const QString &file)
{
    QFile rmfile(file);
    if (!rmfile.remove(file)) {
	factory->interpreter()->throwError(QString::fromLatin1("File %1 could not be removed: %2")
					   .arg(file).arg(rmfile.errorString()));
    }
}

/********************************************************************************
 * class QSFile
 */
QSFile::QSFile(const QString &fileName, QSInterpreter *i)
    : file(new QFile(fileName)), interpreter(i)
{
}

QSFile::~QSFile()
{
    delete file;
}


void QSFile::open(int accessMode)
{
    if (accessMode == Append)
	accessMode |= WriteOnly;
    if (!file->open(QIODevice::OpenMode(accessMode))) {
	interpreter->throwError(QString::fromLatin1("Could not open file '%1':  %2")
				.arg(file->fileName()).arg(file->errorString()));
    }
}

QString QSFile::read()
{
    if (!file->isOpen()) {
	interpreter->throwError(QString::fromLatin1("File '") + file->fileName() + QString::fromLatin1("' is not open"));
	return QString::null;
    }
    return QString::fromLocal8Bit(file->readAll());
}

QString QSFile::readLine()
{
    return QString::fromLocal8Bit(file->readLine(16384));
}


QStringList QSFile::readLines()
{
    return read().split(QString::fromLatin1("\n"));
}

void QSFile::write(const QString &data, int length)
{
    if (length<0)
	length = data.length();
    int written = file->write(data.toLocal8Bit());
    if (written != length) {
	interpreter->throwError(QString::fromLatin1("Failed to write file '%1': %2")
				.arg(file->fileName()).arg(file->errorString()));
    }
}

void QSFile::remove()
{
    if (!file->remove()) {
	interpreter->throwError(QString::fromLatin1("Failed to remove file '%1': %2")
				.arg(file->fileName()).arg(file->errorString()));
    }
}

int QSFile::readByte()
{
    char c;
    bool ok = file->getChar(&c);
    if (!ok) {
	interpreter->throwError(QString::fromLatin1("Failed to read byte from file '%1': %2")
				.arg(file->fileName()).arg(file->errorString()));
    }
    return c;
}

void QSFile::writeByte(int byte)
{
    bool ok = file->putChar(char(byte));
    if (!ok) {
	interpreter->throwError(QString::fromLatin1("Failed to write byte to file '%1': %2")
				.arg(file->fileName()).arg(file->errorString()));
    }
}

/********************************************************************************
 * class QSDirStatic
 */
QStringList QSDirStatic::drives() const
{
    QFileInfoList lst = QDir::drives();
    QStringList driveNames;
    for (int i=0; i<lst.size(); ++i) {
	driveNames << lst.at(i).absoluteFilePath();
    }
    return driveNames;
}

void QSDirStatic::setCurrent(const QString &dir)
{
    if (!QDir::setCurrent(dir))
	factory->interpreter()->throwError(QString::fromLatin1("Failed to set current directory to %1")
					   .arg(dir));
}


/********************************************************************************
 * class QSDir
 */
void QSDir::rename(const QString &oldName, const QString &newName)
{
	if (!dir->rename(QDir::toNativeSeparators(oldName), QDir::toNativeSeparators(newName)))
	interpreter->throwError(QString::fromLatin1("Failed to rename '%1' to '%2'").arg(oldName).arg(newName));
}

void QSDir::remove(const QString &name) const
{
    if (!dir->remove(name))
	interpreter->throwError(QString::fromLatin1("Failed to remove '%1'").arg(name));
}

void QSDir::rmdir(const QString &name) const
{
    if (!dir->rmdir(name.isEmpty() ? dir->absolutePath() : name))
	interpreter->throwError(QString::fromLatin1("Failed to remove directory '%1'").arg(name));
}

void QSDir::mkdir(const QString &name) const
{
    if (!dir->mkdir(name.isEmpty() ? dir->absolutePath() : name))
	interpreter->throwError(QString::fromLatin1("Failed to make directory '%1'").arg(name));
}

static bool qs_rm_dirs(QDir *dir)
{
    if (!dir->exists())
	return false;

    QStringList files = dir->entryList(QDir::Files | QDir::Hidden | QDir::System);
    for (QStringList::ConstIterator fit = files.begin(); fit!=files.end(); ++fit)
	if (!dir->remove(dir->filePath(*fit)))
	    return false;

    QStringList dirs = dir->entryList(QDir::Dirs | QDir::Hidden | QDir::System);
    for (QStringList::ConstIterator it = dirs.begin(); it!=dirs.end(); ++it) {
	if ((*it) == QString::fromLatin1(".") || (*it) == QString::fromLatin1(".."))
	    continue;
	dir->cd(*it);
	bool del = qs_rm_dirs(dir);
	dir->cdUp();
	if (!del)
	    return del;
    }

    if (!dir->rmdir(dir->absolutePath()))
	return false;

    return true;
}

void QSDir::rmdirs(const QString &name) const
{
    bool usesTemp = false;
    QDir *tmpdir;
    if (name.isEmpty()) {
	tmpdir = dir;
    } else {
	tmpdir = new QDir( QFileInfo(name).isRelative() ? dir->filePath(name) : name );
	usesTemp = true;
    }
    if (!qs_rm_dirs(tmpdir))
	    interpreter->throwError(QString::fromLatin1("Failed to remove directory structure: '%1'")
				    .arg(tmpdir->absolutePath()));
    if (usesTemp)
	delete tmpdir;
}


void QSDir::mkdirs(const QString &name) const
{
    // Use current, absolute or relative depending on name.
    QString finalDir;
    if (name.isEmpty())
	finalDir = dir->absolutePath();
    else if (QFileInfo(name).isRelative())
	finalDir = dir->filePath(name);
    else
	finalDir = name;

    // Split up
    finalDir = finalDir.replace(QString::fromLatin1("\\"), QString::fromLatin1("/"));
    QStringList dirs = finalDir.split(QString::fromLatin1("/"));
    QStringList::ConstIterator it = dirs.begin();
    QDir tmpdir(finalDir.startsWith(QString::fromLatin1("/")) ? QString::fromLatin1("/") + *it : *it);
    ++it;
    do {
	if (it == dirs.end())
	    break;
	if (!tmpdir.exists(*it)) {
	    if (!tmpdir.mkdir(*it)) {
		interpreter->throwError(QString::fromLatin1("Failed to create directory %1")
					.arg(tmpdir.filePath(*it)));
		return;
	    }
	}
	tmpdir.cd(*it);
	++it;
    } while (it != dirs.end());
}


QStringList QSDir::entryList(const QString &filter, int filterSpec, int sortSpec) const
{
    return dir->entryList(QStringList(filter), QDir::Filters(filterSpec), QDir::SortFlags(sortSpec));
}


void QSDir::cd(const QString &dirName) const
{
    if (!dir->cd(dirName))
	interpreter->throwError(QString::fromLatin1("Failed to change directory to %1").arg(dirName));
}

void QSDir::cdUp() const
{
    if (!dir->cdUp())
	interpreter->throwError(QString::fromLatin1("Failed to change to parent directory"));
}

QString QSDir::filePath(const QString &file) const
{
    return dir->filePath(file);
}

QString QSDir::absFilePath(const QString &file) const
{
    return dir->absoluteFilePath(file);
}

void QSDir::setCurrent() const
{
    if (!QDir::setCurrent(dir->absolutePath())) {
	interpreter->throwError(QString::fromLatin1("Failed to set '%1' to current directory")
				.arg(dir->absolutePath()));
    }
}


/********************************************************************************
 * class QSProcessStatic
 */
int QSProcessStatic::execute(const QStringList &command, const QString &stdinBuffer)
{
    QStringList commands = command;
    if (commands.size() == 1 && commands[0].contains(' ')) {
        commands = commands[0].split(QString::fromLatin1(" "));
    }
    out = err = QString::null;
    QSBlockingProcess pl;
    QString program = commands.takeFirst();
    pl.start(program, commands);
    if (pl.error() == QProcess::FailedToStart) {
	factory->interpreter()->throwError(QString::fromLatin1("Failed to run process: '%1'")
					   .arg(command.join(QString::fromLatin1(" "))));
        return -1;
    }
    if (!stdinBuffer.isEmpty()) {
	pl.write(stdinBuffer.toLocal8Bit());
    }
    pl.enter();
    int retCode = pl.exitCode();
    out = QString::fromLocal8Bit(pl.readAllStandardOutput());
    err = QString::fromLocal8Bit(pl.readAllStandardError());
    return retCode;
}

int QSProcessStatic::executeNoSplit(const QStringList &command, const QString &stdinBuffer)
{
    out = err = QString::null;
    QSBlockingProcess pl;
    QStringList commands = command;
    QString program = commands.takeFirst();
    pl.start(program, commands);
    if (pl.error() == QProcess::FailedToStart) {
	factory->interpreter()->throwError(QString::fromLatin1("Failed to run process: '%1'")
					   .arg(command.join(QString::fromLatin1(" "))));
        return -1;
    }
    if (!stdinBuffer.isEmpty()) {
	pl.write(stdinBuffer.toLocal8Bit());
    }
    pl.enter();
    int retCode = pl.exitCode();
    out = QString::fromLocal8Bit(pl.readAllStandardOutput());
    err = QString::fromLocal8Bit(pl.readAllStandardError());
    return retCode;
}

/********************************************************************************
 * class QSProcess
 */
QSProcess::QSProcess(QSUtilFactory *f, const QStringList &args)
    : factory(f)
{
    process = new QProcess(this);
    setArguments(args);

    connect(process, SIGNAL(readyReadStandardOutput()), this, SIGNAL(readyReadStdout()));
    connect(process, SIGNAL(readyReadStandardError()), this, SIGNAL(readyReadStderr()));
    connect(process, SIGNAL(finished(int)), this, SIGNAL(processExited()));
    connect(process, SIGNAL(error(QProcess::ProcessError)), this, SIGNAL(processExited()));
    connect(process, SIGNAL(bytesWritten(qint64)), this, SLOT(wroteBytes(qint64)));

    m_bytes_to_write = 0;
}

void QSProcess::start(QStringList *env)
{
    if (env)
        process->setEnvironment(*env);

    QStringList args = m_arguments;
    QString command = args.takeFirst();

    process->start(command, args);

    if (process->error() == QProcess::FailedToStart) {
	factory->interpreter()->throwError(QString("Failed to start process: '%1' - '%2'")
					   .arg(arguments().join(QString::fromLatin1(" ")))
                                           .arg(process->errorString()));
    }
}

void QSProcess::launch(const QString &buf, QStringList *env)
{
    start(env);

    QByteArray data_to_write = buf.toLocal8Bit();
    m_bytes_to_write = data_to_write.length();
    process->write(data_to_write);
}

void QSProcess::wroteBytes(qint64 bytes)
{
    if (m_bytes_to_write > 0) {
        m_bytes_to_write -= bytes;
        if (m_bytes_to_write <= 0)
            emit launchFinished();
    }

    emit wroteToStdin();
}
