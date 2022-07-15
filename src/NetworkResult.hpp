#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace EuleHakenBot {

class NetworkResult
{
public:
    NetworkResult(const QByteArray& data, int status);

    QJsonObject jsonObject() const;;
    QJsonDocument jsonDocument() const;;

    const QByteArray& getData() const;;

    int status() const;;

private:
    QByteArray _data;
    int _status;
};

}  // namespace EuleHakenBot
