#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QThread>

namespace EuleHakenBot {

// Borrowed from https://github.com/Chatterino/chatterino2/blob/master/src/common/NetworkManager.hpp

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    static QNetworkAccessManager accessManager;
    static QThread workerThread;

    static void init();
    static void deinit();
};

}  // namespace EuleHakenBot
