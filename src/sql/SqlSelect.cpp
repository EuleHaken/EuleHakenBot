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

}  // namespace EuleHakenBot
