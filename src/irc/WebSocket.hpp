#pragma once

#include "CommandHandler.hpp"
#include "WebSocketCommandHandler.hpp"
#include "WebSocketCommands.hpp"
#include "messages/IrcMessage.hpp"
#include "messages/PrivmsgMessage.hpp"

#include <QHash>
#include <QList>
#include <QObject>
#include <QUrl>
#include <QWebSocket>
#include <functional>

namespace EuleHakenBot {

/**
 * @brief The WebSocket class handles connection between Web Sockets and User (client)
 */
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

    QWebSocket& getSocket();

    //template <class T>
    //void registerCommandHandler(const WebSocketCommands command, void(*handler)(const T&));
    // // void registerCommandHandler(const QString& command);

    // This is what we wanted to achieve with registerCmdHandler, but simpler, but didnt work :(
    //void setDefaultCommandHandler(void (*handler)(const IrcMessage&));
    void setDefaultCommandHandler(
        std::function<void(const IrcMessage&)> handler);
    void setPrivmsgHandler(std::function<void(const PrivmsgMessage&)> handler);

    void setSocket(const QWebSocket& newSocket);

private slots:
    void onConnected();
    void onIncomingMessage(const QString& message);
    // void onErrors();

private:
    void _write(const QString& text);

    void _defaultPingHandler(const IrcMessage& message);

private:
    QWebSocket _socket;
    bool _isConnected;
    QStringList _messageQueue;

    QUrl _url;

    QString _nick;
    QString _pass;

    //IrcMessage _defaultHandler;
    //PrivmsgMessage _privmsgHandler;

    //WebSocketCommandHandler<IrcMessage> _defaultHandler;
    //WebSocketCommandHandler<PrivmsgMessage> _privmsgHandler;

    //void (WebSocket::*_defaultHandler)(const IrcMessage&);
    //void (WebSocket::*_privmsgHandler)(const PrivmsgMessage&);
    //void (WebSocket::*_pingHandler)(const IrcMessage& message);

    //std::function<void(const IrcMessage&)> _defaultHandler;
    //std::function<void(const PrivmsgMessage&)> _privmsgHandler;
    //std::function<void(const IrcMessage& message)> _pingHandler;

    QHash<QString, QList<CommandHandler*>> _commandHandlers;
    // const? const Handler&?

public:
    void setHandlerTest(const QString& command, CommandHandler& handler);
};

}  // namespace EuleHakenBot
