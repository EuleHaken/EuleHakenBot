#include "SqlInsert.hpp"

#include <QDir>

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

}  // namespace EuleHakenBot
