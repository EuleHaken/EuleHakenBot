#include "SqlSelect.hpp"

namespace EuleHakenBot {

SqlSelect::SqlSelect(const QString& table)
    : _table{table}
{
    this->_db = QSqlDatabase::database("database");
}

SqlSelect& SqlSelect::field(const QString& name)
{
    this->_fields << name;

    return *this;
}

SqlSelect& SqlSelect::fields(const QStringList& names)
{
    for (const auto& name : names)
    {
        this->_fields << name;
    }

    return *this;
}

}  // namespace EuleHakenBot
