#include "IrcClient.hpp"

namespace EuleHakenBot {

IrcClient::IrcClient(QObject* parent)
    : QObject{parent}
    , _isConnected{false}
    , _useSSL{false}
{
    this->_socket = new QSslSocket(parent);

    this->connect(this->_socket, &QSslSocket::connected, this,
                  &IrcClient::onConnected);
    this->connect(this->_socket, &QSslSocket::readyRead, this,
                  &IrcClient::onReadyRead);
}

IrcClient* IrcClient::setHost(const QString& host)
{
    this->_host = host;
    return this;
}

IrcClient* IrcClient::setPort(const quint16& port)
{
    this->_port = port;
    return this;
}

IrcClient* IrcClient::setNick(const QString& nick)
{
    this->_nick = nick;
    return this;
}

IrcClient* IrcClient::setReal(const QString& real)
{
    this->_real = real;
    return this;
}

IrcClient* IrcClient::setUser(const QString& user)
{
    this->_user = user;
    return this;
}

IrcClient* IrcClient::setPass(QString& pass)
{
    if (!pass.startsWith("oauth:"))
        pass.prepend("oauth:");
    this->_pass = pass;

    return this;
}

IrcClient* IrcClient::setUseSSL(bool ssl)
{
    this->_useSSL = ssl;
    return this;
}

void IrcClient::onConnected()
{
    this->_isConnected = true;
    qInfo() << "Connected!";
}

void IrcClient::onReadyRead()
{
    while (this->_socket->canReadLine())
    {
        QString line = this->_socket->readLine();
        line.remove("\r\n");

        emit this->incomingMessage(IrcMessage::parse(line));
        qInfo() << "Read line: " << line;
    }
}

void IrcClient::connectToServer()
{
    if (this->_useSSL)
    {
        this->_socket->connectToHostEncrypted(this->_host, this->_port);
        this->_authenticate();
    }
    else
    {
        this->_socket->connectToHost(this->_host, this->_port);
        this->_authenticate();
    }
}

void IrcClient::_authenticate()
{
    this->_write(QString("PASS %1").arg(this->_pass));
    this->_write(QString("NICK %1").arg(this->_nick));
}

void IrcClient::_write(const QString& text)
{
    this->_socket->write(QString("%1\r\n").arg(text).toUtf8());
}

}  // namespace EuleHakenBot
