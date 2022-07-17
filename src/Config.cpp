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

}  // namespace EuleHakenBot
