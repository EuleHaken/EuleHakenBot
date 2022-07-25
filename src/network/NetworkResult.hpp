#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace EuleHakenBot {

class NetworkResult
{
    Q_DISABLE_COPY(NetworkResult)

public:
    explicit NetworkResult(const QByteArray& data, int status);

    QJsonDocument jsonDocument() const;
    QJsonObject jsonObject() const;

    const QByteArray& getData() const;

    int status() const;

private:
    QByteArray _data;
    int _status;
};

}  // namespace EuleHakenBot
