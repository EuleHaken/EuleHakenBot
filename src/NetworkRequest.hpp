#pragma once

#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrl>
#include "NetworkData.hpp"
#include "NetworkManager.hpp"
#include "NetworkRequestType.hpp"

namespace EuleHakenBot {

class NetworkRequest
{
public:
    NetworkRequest(const QString& url,
                   const NetworkRequestType& type = NetworkRequestType::GET);

    NetworkRequest(const QUrl& url,
                   const NetworkRequestType& type = NetworkRequestType::GET);

    NetworkRequest onSuccess(std::function<void(NetworkResult)> cb);
    NetworkRequest onError(std::function<void(NetworkResult)> cb);

    NetworkRequest setType(const NetworkRequestType& newType);

    NetworkRequest setHeader(const char* key, const char* value);

    NetworkRequest setTimeout(const unsigned long& timeout = 2500);

    void execute();

private:
    void _execute(const NetworkData& data);

private:
    NetworkData _data;
};

}  // namespace EuleHakenBot
