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

const QMap<QString, QJsonValue>& Config::getData() const
{
    return this->_data;
}

}  // namespace EuleHakenBot
