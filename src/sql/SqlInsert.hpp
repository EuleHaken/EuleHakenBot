#pragma once

#include <QSqlDatabase>
#include <QString>
#include <QStringList>

namespace EuleHakenBot {

class SqlInsert final
{
private:
    using SuccessCallback = std::function<void(const QSqlQuery&)>;
    using ErrorCallback = std::function<void(const QSqlQuery&)>;

    using DefaultCallback = std::function<Ret(In...)>;

public:
    /*!
     * \param table Table to insert into
     * \param database Database to insert into. Must not end with anything else than `.db`
     *
     * Creates a sql `INSERT` query
     */
    SqlInsert(const QString& table);

public:
    SqlInsert& data(const QString& key, const QString& value);

    SqlInsert& onSuccess(const SuccessCallback& cb);
    SqlInsert& onError(const ErrorCallback& cb);

    void exec();

private:
    QSqlDatabase _db;

    QString _table;

    QStringList _keys;
    QStringList _vals;

    SuccessCallback
        _onSuccess;          //  = DefaultCallback<void, const QSqlQuery&>();
    ErrorCallback _onError;  //  = DefaultCallback<void, const QSqlQuery&>();
};

}  // namespace EuleHakenBot
