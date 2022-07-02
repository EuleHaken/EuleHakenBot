#pragma once

#include "IrcMessage.hpp"
#include "MessageHandler.hpp"

#include <QObject>
#include <QSslSocket>

namespace EuleHakenBot {

class IrcClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(IrcClient)
public:
    explicit IrcClient(QObject* parent = nullptr);

signals:
    void incomingMessage(const EuleHakenBot::IrcMessage& message);
    /* inline */ void connected();

private slots:
    void onConnected();
    void onReadyRead();
    // virtual void onIncomingMessage(const EuleHakenBot::IrcMessage& message);

public:
    void connectToServer();

    //void registerCommandHandler(const QString& command,
    //const MessageHandler& handler);

    //void join(const QString& channel);
    //void join(const IrcChannel& channel);

    //void part(const QString& channel);
    //void part(const IrcChannel& channel);

    IrcClient* setHost(const QString& host);
    IrcClient* setPort(const quint16& port);

    IrcClient* setNick(const QString& nick);
    IrcClient* setReal(const QString& real);
    IrcClient* setUser(const QString& user);
    IrcClient* setPass(QString& pass);

    IrcClient* setUseSSL(bool ssl);

private:
    //void sendRawMessage(const QString& message);
    void _authenticate();
    void _write(const QString& text);

private:
    QSslSocket* _socket;
    bool _isConnected;
    bool _useSSL;

    QString _host;
    quint16 _port;

    QString _nick;
    QString _real;
    QString _user;

    QString _pass;
};

}  // namespace EuleHakenBot
