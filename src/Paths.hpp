#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QString>

namespace EuleHakenBot {

class Paths
{
    Q_DISABLE_COPY(Paths)

private:
    Paths();

private:
    static Paths& getInstance();

public:
    static const QDir& getChannelsDir();
    static const QDir& getRootDir();
    static const QDir& getCommandsDir();

    static const QString& getRootDirPath();

private:
    QString _rootDirPath;

    QDir _rootDir;
    QDir _channelsDir;
    QDir _commandsDir;
};

}  // namespace EuleHakenBot
