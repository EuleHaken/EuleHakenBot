#pragma once

#include "NetworkData.hpp"
#include "NetworkManager.hpp"
#include "NetworkResult.hpp"

#include <functional>

namespace EuleHakenBot {

class NetworkRequest
{
public:
    NetworkRequest(const QString& url,
                   const NetworkRequestType& type = NetworkRequestType::GET);

    NetworkRequest(const QUrl& url,
                   const NetworkRequestType& type = NetworkRequestType::GET);

    NetworkRequest& onSuccess(const SuccessCallback& cb);
    NetworkRequest& onError(const ErrorCallback& cb);

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
