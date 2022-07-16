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

public:
    static Paths& getInstance();

    const QDir& getChannelsDir() const;
    const QDir& getRootDir() const;
    const QString& getRootDirPath() const;

private:
    QString _rootDirPath;
    QDir _rootDir;

    QDir _channelsDir;
};

}  // namespace EuleHakenBot
