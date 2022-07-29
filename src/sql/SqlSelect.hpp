#pragma once

#include <QMap>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVariant>

namespace EuleHakenBot {

class SqlSelect
{
private:
    using SuccessCallback = std::function<void(const QVariant&)>;
    using ErrorCallback = std::function<void(const QSqlQuery&)>;

public:
    SqlSelect(const QString& table);

public:
    SqlSelect& field(const QString& name);
    SqlSelect& fields(const QStringList& names);

    SqlSelect& where(const QString& key, const QString& value);

    SqlSelect& single();

    SqlSelect& onSuccess(const SuccessCallback& cb);
    SqlSelect& onError(const ErrorCallback& cb);

    void exec();

private:
    QSqlDatabase _db;

    QString _table;

    QStringList _fields;

    QStringList _where;

    bool _single{false};

    SuccessCallback _onSuccess;
    ErrorCallback _onError;
};

}  // namespace EuleHakenBot
