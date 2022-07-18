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
    static void insert(const QString& key, const QJsonValue& value,
                       const bool& updateIfExists = true);
    static void update(const QString& key, const QJsonValue& newValue);

    /**
     * @brief exists Checks if key exists
     * @param key Key to check
     * @return true if key exists - false if not
     */
    static bool exists(const QString& key);

    /**
     * @brief hasValue Checks if key exists and has a value (not null)
     * @param key Key to check
     * @return true if value exists and is not null - false if value does not exist or it's null
     */
    static bool hasValue(const QString& key);

public:
    //const QMap<QString, QJsonValue>& getDataAsMap() const;

    const QJsonObject& getData() const;

private:
    //QMap<QString, QJsonValue> _dataAsMap;

    QJsonObject _data;
};

}  // namespace EuleHakenBot
