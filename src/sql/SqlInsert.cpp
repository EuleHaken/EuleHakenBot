#include "SqlInsert.hpp"
#include "SqlManager.hpp"
#include "SqlWorker.hpp"

#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

namespace EuleHakenBot {

SqlInsert::SqlInsert(const QString& table)
    : _table{table}
{
    this->_db = QSqlDatabase::database("database");
}

SqlInsert& SqlInsert::data(const QString& key, const QString& value)
{
    // TODO escape key and value here (prevent sql injection?)
    this->_keys << QString("\"%1\"").arg(key);
    this->_vals << QString("\"%1\"").arg(value);

    return *this;
}

SqlInsert& SqlInsert::onSuccess(const SuccessCallback& cb)
{
    this->_onSuccess = cb;

    return *this;
}

SqlInsert& SqlInsert::onError(const ErrorCallback& cb)
{
    this->_onError = cb;

    return *this;
}

void SqlInsert::exec()
{
    SqlWorker requester;
    SqlWorker* worker = new SqlWorker;
    worker->moveToThread(&SqlManager::workerThread);

    auto onMakeQuery = [self = std::move(*this)]() mutable {
        if (self._table.isEmpty())
        {
            qWarning() << "cannot create insert query with no table provided!";
            return;
        }

        if (self._keys.length() == 0 || self._vals.length() == 0)
        {
            qWarning() << "cannot create insert query with no keys/values";
            return;
        }

        const QString& baseQuery =
            QString("INSERT INTO `%1` (%2) VALUES (%3);").arg(self._table);

        const QString& keys = self._keys.join(", ");
        const QString& values = self._vals.join(", ");

        const QString& finalQuery = baseQuery.arg(keys, values);

        QSqlQuery result = self._db.exec(finalQuery);
        if (result.lastError().type() != QSqlError::NoError)
        {
            if (self._onError)
            {
                self._onError(result);
            }
            else
            {
                qWarning() << "Insert query had an error:"
                           << result.lastError();
            }

            return;
        }

        if (self._onSuccess)
        {
            self._onSuccess(result);
        }
    };

    QObject::connect(&requester, &SqlWorker::makeQuery, worker,
                     [worker, &onMakeQuery, self = std::move(*this)]() mutable {
                         onMakeQuery();

                         self._db.close();
                         delete worker;
                     });

    emit requester.makeQuery();
}

}  // namespace EuleHakenBot
