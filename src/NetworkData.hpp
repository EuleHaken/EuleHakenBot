#pragma once

#include "NetworkRequestType.hpp"
#include "NetworkResult.hpp"

#include <QNetworkRequest>
#include <functional>

namespace EuleHakenBot {

struct NetworkData
{
    NetworkRequestType type;

    QNetworkRequest request;

    std::function<void(NetworkResult&)> onSuccess;
    std::function<void(NetworkResult&)> onError;
};

}  // namespace EuleHakenBot
