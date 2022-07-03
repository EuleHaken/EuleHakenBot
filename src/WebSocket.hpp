#pragma once

#include "IrcMessage.hpp"

#include <QObject>
#include <QUrl>
#include <QWebSocket>

namespace EuleHakenBot {

/**
 * @brief The WebSocket class handles connection between Web Sockets and User (client)
 */
class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(QObject* parent = nullptr);

public:
    /**
     * @brief Connects to the Web Socket
     */
    void connectToHost();

    /**
     * @brief Sets the nickname (NICK) for the client
     * @param nick nickname
     */
    WebSocket* setNick(const QString& nick);

    /**
     * @brief Sets the password (PASS) for the client
     * @param pass password
     */
    WebSocket* setPass(const QString& pass);

    /**
     * @brief Sets the url we should connect to
     * @param url Url
     */
    WebSocket* setUrl(const QString& url);

    /**
     * @brief Sends raw websocket/irc text/commands to the socket
     * @param text Text to send
     *
     * If we can't send messages to the socket yet - e.g. if its not connected yet -
     * we push the message into a queue. As soon as we are connected, all messages
     * in this queue get sent
     */
    void sendRaw(const QString& text);

private slots:
    void onConnected();
    void onIncomingMessage(const IrcMessage& message);
    void onIncomingMessage(const QString& message);
    // void onErrors();

private:
    void _write(const QString& text);

private:
    QWebSocket _socket;
    bool _isConnected;
    QStringList _messageQueue;

    QUrl _url;

    QString _nick;
    QString _pass;
};

}  // namespace EuleHakenBot
