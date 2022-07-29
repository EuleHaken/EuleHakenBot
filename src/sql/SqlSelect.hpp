#pragma once

#include <QSqlDatabase>
#include <QString>

namespace EuleHakenBot {

class SqlSelect
{
public:
    SqlSelect(const QString& table);

private:
    QSqlDatabase _db;

    QString _table;
};

}  // namespace EuleHakenBot
