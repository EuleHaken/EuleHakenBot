#include "Config.hpp"

namespace EuleHakenBot {

Config::Config()
{
    QDir root = Paths::getInstance().getRootDir();

    QFile configFile(root.absoluteFilePath("config.json"));
    if (!configFile.open(QFile::ReadWrite))
    {
        qFatal("Unable to open/create config.json file!");
        return;
    }

    const auto contentAsObject =
        QJsonDocument::fromJson(configFile.readAll()).object();

    const auto keys = contentAsObject.keys();
    for (const auto& key : keys)
    {
        this->_data.insert(key, contentAsObject[key]);
    }

    configFile.close();
}

Config& Config::getInstance()
{
    static Config instance;
    return instance;
}

QJsonValue Config::get(const QString& key)
{
    return getInstance()._data.value(key);
}

void Config::insert(const QString& key, const QJsonValue& value,
                    const bool& updateIfExists)
{
    auto& instance = getInstance();
    auto& data = instance._data;
    if (data.contains(key) && updateIfExists)
    {
        update(key, value);
        return;
    }

    QDir root = Paths::getInstance().getRootDir();
    QFile configFile(root.absoluteFilePath("config.json"));
    if (!configFile.open((QFile::ReadWrite | QFile::Truncate | QFile::Text)))
    {
        qFatal("Unable to open/create config.json file!");
        return;
    }

    QJsonObject obj;
    for (const auto& key : data.keys())
    {
        obj.insert(key, data[key]);
    }

    obj.insert(key, value);

    QJsonDocument doc(obj);
    auto bytes = doc.toJson();
    configFile.write(bytes);

    data.insert(key, value);

    configFile.close();

    qInfo() << getInstance()._data;
}

void Config::update(const QString& key, const QJsonValue& newValue)
{
    auto& instance = getInstance();
    auto& data = instance._data;
    if (!data.contains(key))
    {
        qInfo() << "Key" << key << "does not exist!";
        return;
    }

    auto oldValue = data.value(key);
    if (oldValue == newValue)
    {
        qInfo() << "Old value and new value are the same!";
        return;
    }

    // replace value of key with newValue
    data.remove(key);
    data.insert(key, newValue);

    QDir root = Paths::getInstance().getRootDir();
    QFile configFile(root.absoluteFilePath("config.json"));
    if (!configFile.open((QFile::ReadWrite | QFile::Truncate | QFile::Text)))
    {
        qFatal("Unable to open/create config.json file!");
        return;
    }

    QJsonObject obj;
    for (const auto& key : data.keys())
    {
        obj.insert(key, data[key]);
    }

    QJsonDocument doc(obj);
    auto bytes = doc.toJson();
    configFile.write(bytes);

    configFile.close();
}

bool Config::exists(const QString& key)
{
    auto value = Config::get(key);
    return !value.isUndefined();
}

bool Config::hasValue(const QString& key)
{
    auto value = Config::get(key);
    return !value.isUndefined() && !value.isNull();
}

/*
const QMap<QString, QJsonValue>& Config::getDataAsMap() const
{
    return this->_dataAsMap;
}
*/

const QJsonObject& Config::getData() const
{
    return this->_data;
}

}  // namespace EuleHakenBot
