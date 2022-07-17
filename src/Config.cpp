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

const QMap<QString, QJsonValue>& Config::getData() const
{
    return this->_data;
}

}  // namespace EuleHakenBot
