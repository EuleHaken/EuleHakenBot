#include "NetworkRequest.hpp"

namespace EuleHakenBot {

NetworkRequest::NetworkRequest(const QString& url,
                               const NetworkRequestType& type)
    : _data{new NetworkData()}
{
    this->_data->request.setUrl(QUrl{url});
    this->_data->type = type;
}

NetworkRequest::NetworkRequest(const QUrl& url, const NetworkRequestType& type)
    : _data{new NetworkData()}
{
    this->_data->request.setUrl(url);
    this->_data->type = type;
}

NetworkRequest& NetworkRequest::onSuccess(
    const std::function<void(NetworkResult&)>& cb)
{
    this->_data->onSuccess = cb;
    return *this;
}

NetworkRequest& NetworkRequest::onError(
    const std::function<void(NetworkResult&)>& cb)
{
    this->_data->onError = cb;
    return *this;
}

NetworkRequest& NetworkRequest::setHeader(const char* key, const char* value)
{
    this->_data->request.setRawHeader(key, value);
    return *this;
}

NetworkRequest& NetworkRequest::setPayload(const QByteArray& data)
{
    this->_data->payload = data;
    return *this;
}

void NetworkRequest::execute()
{
    this->_execute(std::move(this->_data));
}

void NetworkRequest::_execute(const std::shared_ptr<NetworkData>& data)
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
            if (data.onError)
            {
                data.onError(result);
            }
            else
            {
                qInfo()
                    << "Error!"
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
