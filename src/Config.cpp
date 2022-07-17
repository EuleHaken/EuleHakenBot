#include "Config.hpp"

namespace EuleHakenBot {

Config::Config()
{
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

void Config::insert(const QString& key, const QJsonValue& value)
{
    auto& instance = getInstance();

    QDir root = Paths::getInstance().getRootDir();
    QFile configFile(root.absoluteFilePath("config.json"));
    if (!configFile.open((QFile::ReadWrite | QFile::Truncate | QFile::Text)))
    {
        qFatal("Unable to open/create config.json file!");
        return;
    }

    auto& data = instance._data;

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

const QMap<QString, QJsonValue>& Config::getData() const
{
    return this->_data;
}

}  // namespace EuleHakenBot
