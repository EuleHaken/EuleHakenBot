#include "NetworkManager.hpp"

namespace EuleHakenBot {

// Borrowed from https://github.com/Chatterino/chatterino2/blob/master/src/common/NetworkManager.cpp

QThread NetworkManager::workerThread;
QNetworkAccessManager NetworkManager::accessManager;

void NetworkManager::init()
{
    NetworkManager::accessManager.moveToThread(&NetworkManager::workerThread);
    NetworkManager::workerThread.start();
}

void NetworkManager::deinit()
{
    NetworkManager::workerThread.quit();
    NetworkManager::workerThread.wait();
}

}  // namespace EuleHakenBot
