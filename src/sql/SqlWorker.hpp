#pragma once

#include <QObject>

namespace EuleHakenBot {

class SqlWorker final : public QObject
{
    Q_OBJECT

signals:
    void makeQuery();
};

}  // namespace EuleHakenBot
