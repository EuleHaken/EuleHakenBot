#include "Helix.hpp"

namespace EuleHakenBot {

Helix::Helix()
{
}

NetworkRequest Helix::makeRequest(const QString &url, QUrlQuery &query)
{
    const QUrl fullUrl(this->baseUrl + url);

    return NetworkRequest(fullUrl);
}

void Helix::getUsers()
{
    QUrlQuery query;
    this->makeRequest("users", query).execute();
}

}  // namespace EuleHakenBot
