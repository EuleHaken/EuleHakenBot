#pragma once

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include <QString>

#include "Paths.hpp"

namespace EuleHakenBot {

class Config
{
    Q_DISABLE_COPY(Config)

private:
    Config();

public:
    static Config& getInstance();
    static QJsonValue get(const QString& key);
    static void insert(const QString& key, const QJsonValue& value);

public:
    const QMap<QString, QJsonValue>& getData() const;

private:
    QMap<QString, QJsonValue> _data;
};

}  // namespace EuleHakenBot
