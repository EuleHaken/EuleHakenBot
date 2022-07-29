#include "SqlInsert.hpp"

#include "Paths.hpp"

#include <QDir>

namespace EuleHakenBot {

SqlInsert::SqlInsert(const QString& table)
    : _table{table}
{
    const QDir& root = Paths::getRootDir();

    QString realDatabaseName = database;
    if (!database.endsWith(".db"))
        realDatabaseName.append(".db");

    const QString& connectionName = root.absoluteFilePath(realDatabaseName);
    if (!QSqlDatabase::contains(connectionName))
    {
        QSqlDatabase::addDatabase("QSQLITE", connectionName);
    }

    this->_db = QSqlDatabase::database(connectionName);
}

}  // namespace EuleHakenBot
