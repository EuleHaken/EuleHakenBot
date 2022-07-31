#pragma once

#include <QNetworkAccessManager>
#include <QThread>

namespace EuleHakenBot {

class NetworkManager : public QObject
{
public:
    static QThread workerThread;
    static QNetworkAccessManager accessManager;

    static void init();
    static void deinit();
};

}  // namespace EuleHakenBot
