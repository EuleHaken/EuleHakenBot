#pragma once

#include <QString>

namespace EuleHakenBot {

class Config
{
    Q_DISABLE_COPY(Config)

private:
    Config();

public:
    static Config& getInstance();
};

}  // namespace EuleHakenBot
