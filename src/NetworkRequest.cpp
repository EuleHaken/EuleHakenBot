#include "NetworkRequest.hpp"
#include "NetworkManager.hpp"
#include "PostToThread.hpp"

namespace EuleHakenBot {

NetworkRequest::NetworkRequest(const QString& url,
                               const NetworkRequestType& type)
    : _data{NetworkData()}
{
    this->_data.request.setUrl(QUrl{url});
    this->_data.type = type;
}

NetworkRequest::NetworkRequest(const QUrl& url, const NetworkRequestType& type)
    : _data{NetworkData()}
{
    this->_data.request.setUrl(url);
    this->_data.type = type;
}

NetworkRequest NetworkRequest::onSuccess(std::function<void(NetworkResult&)> cb)
{
    this->_data.onSuccess = cb;
    return *this;
}

NetworkRequest NetworkRequest::onError(std::function<void(NetworkResult&)> cb)
{
    this->_data.onError = cb;
    return *this;
}

NetworkRequest NetworkRequest::setType(const NetworkRequestType& newType)
{
    this->_data.type = newType;
    return *this;
}

NetworkRequest NetworkRequest::setHeader(const char* key, const char* value)
{
    this->_data.request.setRawHeader(key, value);
    return *this;
}

NetworkRequest NetworkRequest::setTimeout(const unsigned long& timeout)
{
    this->_data.request.setTransferTimeout(timeout);
    return *this;
}

void NetworkRequest::execute()
{
    this->_execute(std::move(this->_data));
}

void NetworkRequest::_execute(const NetworkData& data)
{
    auto reply = [data]() -> QNetworkReply* {
        switch (data.type)
        {
            case NetworkRequestType::GET: {
                return NetworkManager::accessManager.get(data.request);
            }
            case NetworkRequestType::POST: {
                return nullptr;  // TODO
            }
            default: {
                return nullptr;
            }
        }
    }();

    if (reply == nullptr)
    {
        qInfo() << "Invalid request type!";
        return;
    }

    auto handleReply = [data, reply]() mutable {
        QByteArray byteData = reply->readAll();
        auto status =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        NetworkResult result(byteData, status.toInt());

        if (reply->error() != QNetworkReply::NoError)
        {
            qInfo() << "Error!"
                    << "Status:"
                    << reply->attribute(
                           QNetworkRequest::Attribute::HttpStatusCodeAttribute);
            }

            return;
        }

        if (data.onSuccess)
        {
            data.onSuccess(result);
        }

        reply->deleteLater();
    };

    QObject::connect(reply, &QNetworkReply::finished, [data, handleReply]() {
        postToThread([handleReply]() {
            auto cb = std::move(handleReply);
            cb();
        });
    });
}

}  // namespace EuleHakenBot
