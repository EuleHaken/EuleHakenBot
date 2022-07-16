#include "Helix.hpp"

namespace EuleHakenBot {

Helix::Helix()
{
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
    QUrlQuery query;
    this->makeRequest("users", query).execute();
}

}  // namespace EuleHakenBot
