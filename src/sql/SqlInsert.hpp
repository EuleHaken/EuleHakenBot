#pragma once

#include <QSqlDatabase>
#include <QString>

namespace EuleHakenBot {

class SqlInsert final
{
public:
    /*!
     * \param table Table to insert into
     * \param database Database to insert into. Must not end with anything else than `.db`
     *
     * Creates a sql `INSERT` query
     */
    SqlInsert(const QString& table);

public:
    SqlInsert& data(const QString& key, const QString& value);

    void exec();

private:
    QSqlDatabase _db;

    QString _table;

    QStringList _keys;
    QStringList _vals;
};

}  // namespace EuleHakenBot
