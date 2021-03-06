// MIT License
//
// Copyright (c) 2020 Olivier Le Doeuff
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// ──── INCLUDE ────

// Library Headers
#include <Qaterial/TextFile.hpp>
//#include <Qaterial/Logger.hpp>

// Dependencies Headers

// Qt Headers
#include <QFile>
#include <QFileInfo>
#include <QQmlFile>
#include <QUrl>

// Stl Headers

// ──── DECLARATION ────

using namespace qaterial;

// clang-format off
#ifdef NDEBUG
# define LOG_DEV_DEBUG(str, ...) do {} while (0)
#else
# define LOG_DEV_DEBUG(str, ...) Logger::FILE->debug( "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#endif

#ifdef NDEBUG
# define LOG_DEV_INFO(str, ...)  do {} while (0)
#else
# define LOG_DEV_INFO(str, ...)  Logger::FILE->info(  "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#endif

#ifdef NDEBUG
# define LOG_DEV_WARN(str, ...)  do {} while (0)
#else
# define LOG_DEV_WARN(str, ...)  Logger::FILE->warn(  "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#endif
#ifdef NDEBUG
# define LOG_DEV_ERR(str, ...)   do {} while (0)
#else
# define LOG_DEV_ERR(str, ...)   Logger::FILE->error( "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#endif

#define LOG_DEBUG(str, ...)      do {} while (0)//Logger::FILE->debug( "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#define LOG_INFO(str, ...)       do {} while (0)//Logger::FILE->info(  "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#define LOG_WARN(str, ...)       do {} while (0)//Logger::FILE->warn(  "[{}] " str, (void*)(this), ## __VA_ARGS__ )
#define LOG_ERR(str, ...)        do {} while (0)//Logger::FILE->error( "[{}] " str, (void*)(this), ## __VA_ARGS__ )
// clang-format on

// ──── FUNCTIONS ────

TextFile::TextFile(QObject* parent) : QObject(parent)
{
    connect(this,
        &TextFile::errorChanged,
        this,
        [this](const auto& value)
        {
            if(!value.isEmpty())
                LOG_ERR("File Error : {}", value.toStdString());
        });
}

QString TextFile::fileName() const
{
    const QString filePath = QQmlFile::urlToLocalFileOrQrc(_fileUrl);
    const QString fileName = QFileInfo(filePath).fileName();
    if(fileName.isEmpty())
        return "untitled.txt";
    return fileName;
}

QString TextFile::fileType() const { return QFileInfo(fileName()).suffix(); }

bool TextFile::open(QUrl url, int mode)
{
    LOG_DEV_INFO("open url : {}", url.toString().toStdString());
    // Make sure url is valid as a local file
    if(url.isRelative())
        url = "file:" + url.toString();
    setFileUrl(url);
    _error = "";
    const auto localFile = url.toLocalFile();

    if(localFile.isEmpty())
    {
        if(url.isEmpty())
            setError("filename is empty");
        else
            setError(QString("Filename ") + url.toString() + "isn't a valid file url");
        return false;
    }

    const auto qOpenMode = [&]()
    {
        switch(OpenMode(mode))
        {
        case Read: return QFile::OpenModeFlag::ReadOnly;
        case Write: return QFile::OpenModeFlag::WriteOnly;
        default: return QFile::OpenModeFlag::ReadWrite;
        }
    }() | QFile::OpenModeFlag::Text;

    if(!createAndOpenFile(localFile, qOpenMode))
        return false;

    return true;
}

void TextFile::close()
{
    _error = "";
    if(!_file())
    {
        LOG_DEV_WARN("File isn't open.");
        return;
    }

    if(_writeFile)
        _writeFile->commit();
    closeAndDeleteFile();
}

bool TextFile::write(const QString& string)
{
    _error = "";
    if(!isOpen())
    {
        setError("File is close");
        return false;
    }

    const auto buffer = string.toUtf8();
    if(const auto bytesWritten = _file()->write(buffer); bytesWritten != buffer.length())
    {
        setError(_file()->errorString());
        closeAndDeleteFile();
        return false;
    }
    return true;
}

QString TextFile::readAll()
{
    _error = "";
    if(!isOpen())
    {
        setError("File is close");
        return "";
    }

    const auto buffer = _file()->readAll();

    if(_file()->error())
    {
        setError(_file()->errorString());
        closeAndDeleteFile();
        return "";
    }

    return QString(buffer);
}

QFileDevice* TextFile::_file() const
{
    if(_writeFile)
        return _writeFile;
    return _readFile;
}

bool TextFile::createAndOpenFile(const QString& file, QFileDevice::OpenMode mode)
{
    if(_file())
    {
        LOG_WARN("Close file {} before opening {}", fileName().toStdString(), file.toStdString());
        closeAndDeleteFile();
    }

    if(mode & QFile::OpenModeFlag::ReadOnly)
        _readFile = new QFile(file, this);
    else
        _writeFile = new QSaveFile(file, this);

    if(const auto success = _file()->open(mode); !success)
    {
        setError(_file()->errorString());
        closeAndDeleteFile();
        return false;
    }
    setOpen(true);
    return true;
}

void TextFile::closeAndDeleteFile()
{
    setOpen(false);
    if(_file())
        _file()->deleteLater();

    _writeFile = nullptr;
    _readFile = nullptr;
}
