#include "Helix.hpp"

namespace EuleHakenBot {

Helix::Helix()
{
    if (Config::exists("oauthToken"))
    {
        this->oauthToken = Config::get("oauthToken").toString();
    }
    if (Config::exists("clientID"))
    {
        this->clientID = Config::get("clientID").toString();
    }
}

NetworkRequest Helix::makeRequest(const QString& url, const QUrlQuery& query)
{
    assert(!url.startsWith("/"));

    QUrl fullUrl(this->baseUrl.arg(url));
    fullUrl.setQuery(query);

    return NetworkRequest(fullUrl)
        .setHeader("Authorization",
                   QString("Bearer %1").arg(this->oauthToken).toUtf8())
        .setHeader("Client-Id", this->clientID.toUtf8())
        .setHeader("Accept", "application/json");
}

void Helix::getUsers()
{
    this->makeRequest("users").execute();
}

void Helix::getTwitchID(const QString& username,
                        const std::function<void(int)>& onSuccess,
                        const std::function<void(NetworkResult&)>& onError)
{
    QUrlQuery query;
    query.addQueryItem("login", username);

    this->makeRequest("users", query)
        .onSuccess([onSuccess](NetworkResult& result) {
            auto id = result.jsonDocument()["data"]["id"];

            onSuccess(id.toInt(-1));
        })
        .onError([onError](NetworkResult& result) {
            onError(result);  // can prob. just do .onError(onError);
        })
        .execute();
}

void Helix::updateCredentials(const QString& newClientID,
                              const QString& newOauthToken)
{
    this->clientID = newClientID;
    this->oauthToken = newOauthToken;
}

}  // namespace EuleHakenBot
