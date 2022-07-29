#include "Tmi.hpp"

namespace EuleHakenBot {

void Tmi::getChatters(
    const QString& channel,
    const std::function<void(const bool& success, const QJsonObject&)>& cb)
{
    this->makeRequest(QString("group/user/%1/chatters").arg(channel))
        .onSuccess([cb](const NetworkResult& result) {
            if (result.status() != 200)
            {
                cb(false, QJsonObject());
                return;
            }

            const auto& chattersObj =
                result.jsonObject()["chatters"].toObject();
            cb(true, chattersObj);
        })
        .onError([cb](const NetworkResult& result) {
            cb(false, QJsonObject());
        })
        .execute();
}

void Tmi::getChatterCount(const QString& channel,
                          const std::function<void(const int&)>& cb)
{
    this->makeRequest(QString("group/user/%1/chatters").arg(channel))
        .onSuccess([cb](const NetworkResult& result) {
            if (result.status() != 200)
            {
                cb(-1);
                return;
            }

            const int& count = result.jsonObject()["chatter_count"].toInt(-1);
            cb(count);
        })
        .onError([cb](NetworkResult&) {
            cb(-1);
        })
        .execute();
}

Tmi& Tmi::getInstance()
{
    static Tmi instance;
    return instance;
}

NetworkRequest Tmi::makeRequest(const QString& url, const QUrlQuery& query)
{
    assert(!url.startsWith("/"));

    QUrl fullUrl(this->baseUrl.arg(url));
    fullUrl.setQuery(query);

    return NetworkRequest(fullUrl).setHeader("Accept", "application/json");
}

}  // namespace EuleHakenBot
