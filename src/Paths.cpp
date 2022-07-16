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
}

Paths& Paths::getInstance()
{
    static Paths instance;
    return instance;
}

const QDir& Paths::getChannelsDir() const
{
    return this->_channelsDir;
}

const QDir& Paths::getRootDir() const
{
    return this->_rootDir;
}

const QString& Paths::getRootDirPath() const
{
    return this->_rootDirPath;
}

}  // namespace EuleHakenBot
