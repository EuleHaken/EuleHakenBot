#pragma once

#include "NetworkRequestType.hpp"
#include "NetworkResult.hpp"

#include <QByteArray>
#include <QCoreApplication>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <functional>

namespace EuleHakenBot {

using SuccessCallback = std::function<void(NetworkResult&)>;
using ErrorCallback = std::function<void(NetworkResult&)>;

struct NetworkData
{
    Q_DISABLE_COPY(NetworkData) // meh, dont like that :/
    NetworkData() = default;

    SuccessCallback onSuccess;
    ErrorCallback onError;

    NetworkRequestType type;

    QNetworkRequest request;

    QByteArray payload;
};

}  // namespace EuleHakenBot
