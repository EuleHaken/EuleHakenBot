#pragma once

#include <QString>
#include <QUrlQuery>

#include "network/NetworkRequest.hpp"

namespace EuleHakenBot {

class Tmi
{
    Q_DISABLE_COPY(Tmi)

private:
    Tmi() = default;

public:
    /**
     * @brief getChatters Gets all chatters that are currently in provided channel
     * @param channel Channel to look for
     * @param cb Contains the list of chatters - includes their role - and whether or not
     *  the request was successful
     *
     * The roles are:
     *  - broadcaster
     *  - vips
     *  - moderators
     *  - staff
     *  - admins
     *  - global_mods
     *  - viewers
     */
    void getChatters(
        const QString& channel,
        const std::function<void(const bool& success, const QJsonObject&)>& cb);

    /**
     * @brief getChatterCount Gets the amount of currently active chatters in provided channel
     * @param channel Channel to look for
     */
    void getChatterCount(const QString& channel,
                         const std::function<void(const int&)>& cb);

public:
    static Tmi& getInstance();

private:
    NetworkRequest makeRequest(const QString& url,
                               const QUrlQuery& query = QUrlQuery());

private:
    const QString baseUrl = "https://tmi.twitch.tv/%1";
};

}  // namespace EuleHakenBot
