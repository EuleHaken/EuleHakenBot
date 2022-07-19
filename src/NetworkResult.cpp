#include "NetworkResult.hpp"

namespace EuleHakenBot {

NetworkResult::NetworkResult(const QByteArray& data, int status)
    : _data{data}
    , _status{status}
{
}

QJsonObject NetworkResult::jsonObject() const
{
    QJsonDocument doc = QJsonDocument::fromJson(this->_data);
    return doc.object();
}

QJsonDocument NetworkResult::jsonDocument() const
{
    return QJsonDocument::fromJson(this->_data);
}

const QByteArray& NetworkResult::getData() const
{
    return this->_data;
}

int NetworkResult::status() const
{
    return this->_status;
}

}  // namespace EuleHakenBot
