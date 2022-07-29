#include "SqlManager.hpp"

#include "Paths.hpp"

#include <QDir>
#include <QSqlDatabase>

namespace EuleHakenBot {

QThread SqlManager::workerThread;

void SqlManager::init()
{
    const QDir& root = Paths::getRootDir();

    const QString& connectionName = root.absoluteFilePath("database.db");
    if (!root.exists("database.db"))
    {
        QFile(connectionName).open(QFile::ReadWrite);
    }

    // "database" => connection name
    // latter user would look like this: QSqlDatabase::database("database");
    auto tmp = QSqlDatabase::addDatabase("QSQLITE", "database");
    tmp.setDatabaseName(connectionName);

    SqlManager::workerThread.start();
}

void SqlManager::deinit()
{
    SqlManager::workerThread.quit();
    SqlManager::workerThread.wait();
}

}  // namespace EuleHakenBot
