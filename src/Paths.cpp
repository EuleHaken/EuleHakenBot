#include "Paths.hpp"

namespace EuleHakenBot {

Paths::Paths()
    : _rootDirPath{qApp->applicationDirPath()}
    , _rootDir{_rootDirPath}
{
    // Here, we want to check if each directory (see private fields/members)
    // and if they don't, we create those directories

    if (!this->_rootDir.exists("channels"))
    {
        this->_rootDir.mkdir("channels");
    }
    this->_channelsDir = QDir(this->_rootDir.absoluteFilePath("channels"));

    if (!this->_rootDir.exists("commands"))
    {
        this->_rootDir.mkdir("commands");
    }
    this->_commandsDir = QDir(this->_rootDir.absoluteFilePath("commands"));
}

Paths& Paths::getInstance()
{
    static Paths instance;
    return instance;
}

const QDir& Paths::getChannelsDir()
{
    return getInstance()._channelsDir;
}

const QDir& Paths::getRootDir()
{
    return getInstance()._rootDir;
}

const QDir& Paths::getCommandsDir()
{
    return getInstance()._commandsDir;
}

const QString& Paths::getRootDirPath()
{
    return getInstance()._rootDirPath;
}

}  // namespace EuleHakenBot
