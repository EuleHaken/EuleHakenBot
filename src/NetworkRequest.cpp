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

NetworkRequest& NetworkRequest::setTimeout(const unsigned long& timeout)
{
    this->_data->request.setTransferTimeout(timeout);
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
    NetworkWorker requester;

    NetworkWorker* worker = new NetworkWorker;
    worker->moveToThread(&NetworkManager::workerThread);

    auto onUrlRequested = [data, worker]() {
        auto reply = [&]() -> QNetworkReply* {
            switch (data->type)
            {
                case NetworkRequestType::GET: {
                    qInfo() << "Performing GET request!";
                    return NetworkManager::accessManager.get(data->request);
                }
                case NetworkRequestType::POST: {
                    return NetworkManager::accessManager.post(data->request,
                                                              data->payload);
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

        QObject::connect(
            reply, &QNetworkReply::finished, worker,
            [reply, data, worker]() mutable {
                QByteArray bytes = reply->readAll();
                auto status =
                    reply
                        ->attribute(
                            QNetworkRequest::Attribute::HttpStatusCodeAttribute)
                        .toInt();

                NetworkResult result(bytes, status);

                if (reply->error() != QNetworkReply::NoError)
                {
                    if (data->onError)
                    {
                        data->onError(result);
                    }
                    else
                    {
                        qInfo() << "Error:" << result.getData();
                    }
                    return;
                }

                if (data->onSuccess)
                {
                    data->onSuccess(result);
                }
                else
                {
                    qInfo() << "Success:" << result.getData();
                }

                delete worker;
            });
    };

    QObject::connect(&requester, &NetworkWorker::requestUrl, worker,
                     onUrlRequested);

    emit requester.requestUrl();
}

}  // namespace EuleHakenBot
