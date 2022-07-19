#pragma once

#include <QNetworkAccessManager>
#include <QThread>

namespace EuleHakenBot {

// Borrowed from https://github.com/Chatterino/chatterino2/blob/master/src/common/NetworkManager.hpp

class NetworkManager : public QObject
{
public:
    static QThread workerThread;
    static QNetworkAccessManager accessManager;

    static void init();
    static void deinit();
};

}  // namespace EuleHakenBot
