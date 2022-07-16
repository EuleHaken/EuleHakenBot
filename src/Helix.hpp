#pragma once

#include "NetworkRequest.hpp"

#include <QString>
#include <QUrlQuery>

namespace EuleHakenBot {

class Helix
{
public:
    Helix();

    NetworkRequest makeRequest(const QString& url, QUrlQuery& query);

    void getUsers();
    void getChannels();

private:
    QString baseUrl = "https://api.twitch.tv/helix/";
};

}  // namespace EuleHakenBot
