#include "SqlSelect.hpp"
#include "SqlWorker.hpp"

#include <QList>
#include <QMap>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

namespace EuleHakenBot {

SqlSelect::SqlSelect(const QString& table)
    : _table{table}
{
    this->_db = QSqlDatabase::database("database");
}

SqlSelect& SqlSelect::field(const QString& name)
{
    this->_fields << QString("\"%1\"").arg(name);

    return *this;
}

SqlSelect& SqlSelect::fields(const QStringList& names)
{
    for (const auto& name : names)
    {
        this->_fields << QString("\"%1\"").arg(name);
    }

    return *this;
}

SqlSelect& SqlSelect::where(const QString& key, const QString& value)
{
    QString a = QString("\"%1\" = \"%2\"").arg(key, value);

    return *this;
}

SqlSelect& SqlSelect::single()
{
    this->_single = true;

    return *this;
}

SqlSelect& SqlSelect::onSuccess(const SuccessCallback& cb)
{
    this->_onSuccess = cb;

    return *this;
}

SqlSelect& SqlSelect::onError(const ErrorCallback& cb)
{
    this->_onError = cb;

    return *this;
}

void SqlSelect::exec()
{
    SqlWorker requester;
    SqlWorker* worker = new SqlWorker;

    auto onMakeQuery = [self = std::move(*this)]() mutable {
        QString fields =
            self._fields.length() == 0 ? "*" : self._fields.join(", ");

        QString query =
            QString("SELECT %1 FROM \"%2\"").arg(fields, self._table);

        if (self._where.length() > 0)
        {
            QString where = self._where.join(") AND (");
            query.append(QString(" WHERE (%1)").arg(where));
        }

        QSqlQuery result = self._db.exec(query);
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
        QList<QVariant> vals;

        auto record = result.record();
        int columns = record.count();
        while (result.next())
        {
            for (int i = 0; i < columns; i++)
            {
                QMap<QString, QVariant> _map;
                _map.insert(record.fieldName(i), record.field(i).value());

                vals.insert(QVariant(map));
            }
            if (self._single)
                break;
        }

        QVariant v;
        v.toSt

            if (self._onSuccess)
        {
            self._onSuccess(map);
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
