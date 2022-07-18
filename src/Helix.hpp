#pragma once

#include "NetworkRequest.hpp"

#include <QString>
#include <QUrlQuery>
#include <functional>
#include <typeinfo>

namespace EuleHakenBot {

template <typename Type, class... Params>
using DefaultCallback = std::function<Type(Params...)>;

class Helix
{
    Q_DISABLE_COPY(Helix)

private:
    Helix();

    void getUsers();
    void getChannels();

    void getTwitchID(const QString& username,
                     const std::function<void(int)>& onSuccess,
                     const std::function<void(NetworkResult&)>& onError =
                         DefaultCallback<void, NetworkResult&>());

    void updateCredentials(const QString& newClientID,
                           const QString& newOauthToken);

private:
    NetworkRequest makeRequest(const QString& url,
                               const QUrlQuery& query = QUrlQuery());

private:
    const QString baseUrl = "https://api.twitch.tv/helix/%1";

    QString clientID;
    QString oauthToken;
};

}  // namespace EuleHakenBot
