#pragma once

#include <QSqlDatabase>
#include <QString>
#include <QStringList>

namespace EuleHakenBot {

class SqlSelect
{
public:
    SqlSelect(const QString& table);

public:
    SqlSelect& field(const QString& name);
    SqlSelect& fields(const QStringList& names);

private:
    QSqlDatabase _db;

    QString _table;

    QStringList _fields;
};

}  // namespace EuleHakenBot
