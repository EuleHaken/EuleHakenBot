#pragma once

#include <QJsonValue>
#include <QMap>
#include <QString>

namespace EuleHakenBot {

class Config
{
    Q_DISABLE_COPY(Config)

private:
    Config();

public:
    static Config& getInstance();

public:
    const QMap<QString, QJsonValue>& getData() const;

private:
    QMap<QString, QJsonValue> _data;
};

}  // namespace EuleHakenBot
