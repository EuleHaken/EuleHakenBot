#pragma once

#include <QObject>
#include <QThread>

namespace EuleHakenBot {

class SqlManager : public QObject
{
public:
    static QThread workerThread;

    static void init();
    static void deinit();
};

}  // namespace EuleHakenBot
