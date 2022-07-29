#include "SqlSelect.hpp"

namespace EuleHakenBot {

SqlSelect::SqlSelect(const QString& table)
    : _table{table}
{
    this->_db = QSqlDatabase::database("database");
}

}  // namespace EuleHakenBot
