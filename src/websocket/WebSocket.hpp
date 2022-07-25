#pragma once

#include "CommandHandler.hpp"
#include "messages/IrcMessage.hpp"

#include <QHash>
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QWebSocket>

namespace EuleHakenBot {

class WebSocket : public QObject
{
    Q_OBJECT

public:
    explicit WebSocket(QObject* parent = nullptr);

signals:
    void incomingMessage(const IrcMessage& message);

public:
    /**
     * @brief Connects to the Web Socket
     */
    void connectToHost();

    /**
     * @brief Sets the nickname (NICK) for the client
     * @param nick nickname
     */
    WebSocket& setNick(const QString& nick);

    /**
     * @brief Sets the password (PASS) for the client
     * @param pass password
     */
    WebSocket& setPass(const QString& pass);

    /**
     * @brief Sets the url we should connect to
     * @param url Url
     */
    WebSocket& setUrl(const QString& url);

    /**
     * @brief Sends raw websocket/irc text/commands to the socket
     * @param text Text to send
     *
     * If we can't send messages to the socket yet - e.g. if its not connected yet -
     * we push the message into a queue. As soon as we are connected, all messages
     * in this queue get sent
     */
    void sendRaw(const QString& text);

    /**
     * @brief sendMessage sends a message to specified channel
     * @param channel Channel to send message to
     * @param message Message to send
     */
    void sendMessage(const QString& channel, const QString& message);

    QWebSocket& getSocket();

    void setHandler(const QString& command,
                    std::shared_ptr<CommandHandler> handler);

    //# @note Optional: This method should be called before connecting to host

    /**
     * @brief Will join all channels from provided list
     * @param channels Channels to join
     *
     * Channels should not be prefixed with a `#`! This will happen inside the function
     * already
     */
    void joinAll(const QStringList& channels);

    /**
     * @brief join Joins a channel based on its name
     * @param channel Name of channel to join (without `#` prefix!)
     */
    void join(const QString& channel);

private slots:
    void onConnected();
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

    QMap<QString, QList<std::shared_ptr<CommandHandler>>> _commandHandlers;
};

}  // namespace EuleHakenBot
