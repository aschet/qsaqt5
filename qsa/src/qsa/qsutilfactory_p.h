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

#ifndef QSUTILFACTORY_P_H
#define QSUTILFACTORY_P_H

#include "qsinterpreter.h"
#include "qsutilfactory.h"

#include <QtCore/QDir>
#include <QtCore/QDateTime>
#include <QtCore/QEventLoop>
#include <QtCore/QFile>
#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QVariant>

#include <limits.h>

class QSFileStatic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString objectName READ objectName SCRIPTABLE false)
    Q_ENUMS(AccessMode)
public:
    enum AccessMode {
	    ReadOnly  = QIODevice::ReadOnly,
	    WriteOnly = QIODevice::WriteOnly,
	    ReadWrite = QIODevice::ReadWrite,
	    Append    = QIODevice::Append,
	    Truncate  = QIODevice::Truncate,
	    Translate = QIODevice::Text
    };
    QSFileStatic(QSUtilFactory *i) : factory(i) { }

public slots:
    bool exists(const QString &fileName) { return QFile::exists(fileName);}
    void remove(const QString &fileName);
    void write(const QString &fileName, const QString &content);
    QString read(const QString &fileName);

    bool isFile(const QString &fileName) { return QFileInfo(fileName).isFile(); }
    bool isDir(const QString &fileName) { return QFileInfo(fileName).isDir(); }

private:
    QSUtilFactory *factory;
};

class QSFile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ fileName)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QString fullName READ absFileName)
    Q_PROPERTY(QString baseName READ baseName)
    Q_PROPERTY(QString extension READ extension)
    Q_PROPERTY(QString symLink READ symLink)

    Q_PROPERTY(bool exists READ exists)
    Q_PROPERTY(bool readable READ isReadable)
    Q_PROPERTY(bool writable READ isWritable)
    Q_PROPERTY(bool executable READ isExecutable)
    Q_PROPERTY(bool hidden READ isHidden)
    Q_PROPERTY(bool eof READ eof)

    Q_PROPERTY(QDateTime created READ created)
    Q_PROPERTY(QDateTime lastModified READ lastModified)
    Q_PROPERTY(QDateTime lastRead READ lastRead)

    Q_PROPERTY(int size READ size)

    Q_ENUMS(AccessMode)
public:
    enum AccessMode {
	    ReadOnly  = QIODevice::ReadOnly,
	    WriteOnly = QIODevice::WriteOnly,
	    ReadWrite = QIODevice::ReadWrite,
	    Append    = QIODevice::Append,
	    Truncate  = QIODevice::Truncate,
	    Translate = QIODevice::Text
    };

public slots:
    void open(int accessMode);
    void close() { file->close(); }
    void remove();

    int readByte();
    QString read();
    QString readLine();
    QStringList readLines();

    void writeByte(int byte);
    void write(const QString &data, int length = -1);
    void writeLine(const QString &data) { write(data + QString::fromLatin1("\n")); }

public:
    QSFile(const QString &file, QSInterpreter *i);
    ~QSFile();

    QString fileName() const { return QFileInfo(*file).fileName(); }
    QString path() const { return QFileInfo(*file).absolutePath(); }
    QString absFileName() const { return QFileInfo(*file).absoluteFilePath(); }
    QString baseName() const { return QFileInfo(*file).baseName(); }
    QString extension() const { return QFileInfo(*file).completeSuffix(); }
    QString symLink() const { QFileInfo f(*file); return f.isSymLink() ? f.readLink() : QString(); }

    bool exists() const { return file->exists(); }
    bool isReadable() const { return QFileInfo(*file).isReadable(); }
    bool isWritable() const { return QFileInfo(*file).isWritable(); }
    bool isExecutable() const { return QFileInfo(*file).isExecutable(); }
    bool isHidden() const { return QFileInfo(*file).isHidden(); }
    bool eof() const { return file->atEnd(); }

    QDateTime created() const { return QFileInfo(*file).created(); }
    QDateTime lastModified() const { return QFileInfo(*file).lastModified(); }
    QDateTime lastRead() const { return QFileInfo(*file).lastRead(); }

    int size() const { return file->size(); }

private:
    QFile *file;
    QSInterpreter *interpreter;
};


class QSDirStatic : public QObject
{
    Q_OBJECT
    Q_ENUMS(FilterSpec)
    Q_ENUMS(SortSpec)
	Q_PROPERTY(QString objectName READ objectName SCRIPTABLE false)
    Q_PROPERTY(QString current READ current WRITE setCurrent)
    Q_PROPERTY(QString home READ home)
    Q_PROPERTY(QString root READ root)
    Q_PROPERTY(QStringList drives READ drives)

public:
    enum FilterSpec {
        Dirs        = QDir::Dirs,
        Files 		= QDir::Files,
        Drives 		= QDir::Drives,
        NoSymLinks 	= QDir::NoSymLinks,
        All 		= QDir::TypeMask,
        TypeMask 	= QDir::TypeMask,
        Readable 	= QDir::Readable,
        Writable 	= QDir::Writable,
        Executable 	= QDir::Executable,
        RWEMask 	= QDir::PermissionMask,
        Modified 	= QDir::Modified,
        Hidden 		= QDir::Hidden,
        System 		= QDir::System,
        AccessMask 	= QDir::AccessMask
    };

    enum SortSpec {
        Name 		= QDir::Name,
        Time 		= QDir::Time,
        Size 		= QDir::Size,
        Unsorted 	= QDir::Unsorted,
        SortByMask 	= QDir::SortByMask,
        DirsFirst 	= QDir::DirsFirst,
        Reversed 	= QDir::Reversed,
        IgnoreCase 	= QDir::IgnoreCase
    };

public slots:
    QString cleanDirPath(const QString &path) const { return QDir::cleanPath(path); }
	QString convertSeparators(const QString &path) const { return QDir::toNativeSeparators(path); }

public:
    QSDirStatic(QSUtilFactory *f) : factory(f) { };
    void setCurrent(const QString &path);
    QString current() const { return QDir::currentPath(); }
    QString home() const { return QDir::homePath(); }
    QString root() const { return QDir::rootPath(); }
    QStringList drives() const;

private:
    QSUtilFactory *factory;
};

class QSDir : public QObject
{
    Q_OBJECT
    Q_ENUMS(FilterSpec)
    Q_ENUMS(SortSpec)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(QString absPath READ absPath)
    Q_PROPERTY(QString canonicalPath READ canonicalPath)
    Q_PROPERTY(bool readable READ isReadable)
    Q_PROPERTY(bool exists READ exists)
public:
    enum FilterSpec {
        Dirs        = QDir::Dirs,
        Files 		= QDir::Files,
        Drives 		= QDir::Drives,
        NoSymLinks 	= QDir::NoSymLinks,
        All 		= QDir::TypeMask,
        TypeMask 	= QDir::TypeMask,
        Readable 	= QDir::Readable,
        Writable 	= QDir::Writable,
        Executable 	= QDir::Executable,
        RWEMask 	= QDir::PermissionMask,
        Modified 	= QDir::Modified,
        Hidden 		= QDir::Hidden,
        System 		= QDir::System,
        AccessMask 	= QDir::AccessMask
    };

    enum SortSpec {
        Name 		= QDir::Name,
        Time 		= QDir::Time,
        Size 		= QDir::Size,
        Unsorted 	= QDir::Unsorted,
        SortByMask 	= QDir::SortByMask,
        DirsFirst 	= QDir::DirsFirst,
        Reversed 	= QDir::Reversed,
        IgnoreCase 	= QDir::IgnoreCase
    };

public slots:
    QString filePath(const QString &file=QString()) const;
    QString absFilePath(const QString &file=QString()) const;
    void cd(const QString &dirName) const;
    void cdUp() const;

    QStringList entryList(const QString &filter,
			  int filterSpec=-1,
			  int sortSpec=-1) const;

    void mkdir(const QString &dirName = QString()) const;
    void rmdir(const QString &dirName = QString()) const;

    void mkdirs(const QString &dirName = QString()) const;
    void rmdirs(const QString &dirName = QString()) const;

    void remove(const QString &fileName) const;
    void rename(const QString &oldName, const QString &newName);

    bool fileExists(const QString &fileName) const { return dir->exists(fileName); }

    void setCurrent() const;

public:
    QSDir(const QString &path, QSInterpreter *ip) : dir(new QDir(path)), interpreter(ip) { }
    QString name() const { return dir->dirName(); }
    QString path() const { return dir->path(); }
    void setPath(const QString &newPath) const { dir->setPath(newPath); }
    QString absPath() const { return dir->absolutePath(); }
    QString canonicalPath() const { return dir->canonicalPath(); }

    bool isReadable() const { return dir->isReadable(); }
    bool exists() const { return dir->exists(); }

private:
    QDir *dir;
    QSInterpreter *interpreter;
};


class QSBlockingProcess : public QProcess
{
    Q_OBJECT

public:
    QSBlockingProcess()
    {
	connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(exited()));
	connect(this, SIGNAL(finished(int)), this, SLOT(exited()));
        connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(close()));
        m_eventLoop = new QEventLoop(this);
    }

public slots:
    void enter()
    {
        m_eventLoop->exec();
    }

    void exited()
    {
		m_eventLoop->exit();
    }

private slots:
    void close() { closeWriteChannel(); }

private:
    QEventLoop *m_eventLoop;
};

// workaround for nameclash due to existing preprocessor definitions in Microsoft UCRT

#ifdef stdout
#define stdout_lastdef stdout
#undef stdout
#endif

#ifdef stderr
#define stderr_lastdef stderr
#undef stderr
#endif

class QSProcessStatic : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QString objectName READ objectName SCRIPTABLE false)
    Q_PROPERTY(QString stdout READ readStdout)
    Q_PROPERTY(QString stderr READ readStderr)
public:
    QSProcessStatic(QSUtilFactory *f) :
	factory(f)
    {
    }

    QString readStdout() const { return out; }
    QString readStderr() const { return err; }

public slots:
    int execute(const QStringList &command, const QString &stdinBuffer=QString());
    int executeNoSplit(const QStringList &command, const QString &stdinBuffer = QString());
    int execute(const QString &command, const QString &stdinBuffer=QString())
    {
	return execute(QStringList(command), stdinBuffer);
    }

private:
    QString out, err;
    QSUtilFactory *factory;
};

#ifdef stdout_lastdef
#define stdout stdout_lastdef
#endif

#ifdef stderr_lastdef
#define stderr stderr_lastdef
#endif

class QSProcess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString objectName READ objectName SCRIPTABLE false)
    Q_PROPERTY(QStringList arguments READ arguments WRITE setArguments)
    Q_PROPERTY(QString workingDirectory READ workingDirectory WRITE setWorkingDirectory)
    Q_PROPERTY(bool running READ running)
    Q_PROPERTY(int exitStatus READ exitStatus)

public:
    QSProcess(QSUtilFactory *f, const QStringList &args=QStringList());

    QStringList arguments() const { return m_arguments; }
    void setArguments(const QStringList &arguments) { m_arguments = arguments; }
    QString workingDirectory() const
    {
        return QFileInfo(process->workingDirectory()).absoluteFilePath();
    }

    void setWorkingDirectory(const QString &workingDirectory)
    {
        process->setWorkingDirectory(QFileInfo(workingDirectory).absoluteFilePath());
    }

    bool running() const { return process->state() == QProcess::Running; }
    int exitStatus() const { return process->exitCode(); }

public slots:
    void start(QStringList *env=0);
    void launch(const QString &buf, QStringList *env=0);

    QString readStdout()
    {
        process->setReadChannel(QProcess::StandardOutput);
        return QString::fromLocal8Bit(process->read(INT_MAX));
    }

    QString readStderr()
    {
        process->setReadChannel(QProcess::StandardError);
        return QString::fromLocal8Bit(process->read(INT_MAX));
    }

    bool canReadLineStdout()
    {
        process->setReadChannel(QProcess::StandardOutput);
        return process->canReadLine();
    }

    bool canReadLineStderr()
    {
        process->setReadChannel(QProcess::StandardError);
        return process->canReadLine();
    }

    QString readLineStdout()
    {
        process->setReadChannel(QProcess::StandardOutput);
        return QString::fromLocal8Bit(process->readLine());
    }

    QString readLineStderr()
    {
        process->setReadChannel(QProcess::StandardError);
        return QString::fromLocal8Bit(process->readLine());
    }

    void tryTerminate() const { process->terminate(); }
    void kill() const { process->kill(); }
    void writeToStdin(const QString &buffer) {
        qint64 to_write = buffer.length();
        qint64 actual_write = process->write(buffer.toLocal8Bit());
        if (to_write != actual_write) {
            factory->interpreter()->throwError("failed to write to stdin");
        }
        while (process->bytesToWrite() > 0) {
            if (!process->waitForBytesWritten(1000)) {
                factory->interpreter()->throwError("failed to write to stdin");
            }
        }
    }
    void closeStdin() { process->close(); }

private slots:
    void wroteBytes(qint64 bytes);

signals:
    void readyReadStdout();
    void readyReadStderr();
    void processExited();
    void wroteToStdin();
    void launchFinished();

private:
    QStringList m_arguments;
    QProcess *process;
    QSUtilFactory *factory;
    qint64 m_bytes_to_write;
};

#endif
