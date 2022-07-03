#include "WebSocket.hpp"

namespace EuleHakenBot {

WebSocket::WebSocket(QObject* parent)
    : QObject{parent}
    , _isConnected{false}
{
    this->connect(&this->_socket, &QWebSocket::connected, this,
                  &WebSocket::onConnected);

    this->connect(&this->_socket, &QWebSocket::textMessageReceived, this,
                  qOverload<const QString&>(&WebSocket::onIncomingMessage));
}

void WebSocket::onIncomingMessage(const QString& message)
{
    QStringList messages = message.split("\r\n");
    foreach (QString line, messages)
    {
        // Ignore empty lines. Happens, if `message` ends with `\r\n` and we split on `\r\n`, therefore, last `line` will be empty
        // Just try this in JavaScript for example:
        //  const text = "asd\r\ntest\r\n"; text.split("\r\n"); // you will get array like this: ["asd", "test", ""];
        if (line.isEmpty())
            continue;

        if (line.endsWith("\r\n"))
            line.remove("\r\n");

        this->onIncomingMessage(IrcMessage::parse(line));
    }
}

void WebSocket::_write(const QString& text)
{
    this->_socket.sendTextMessage(text);
    this->_socket.flush();
}

void WebSocket::onIncomingMessage(const IrcMessage& message)
{
    qInfo() << "Message: " << message.getRawMessage();
}

void WebSocket::onConnected()
{
    qInfo() << "connected!";
    // maybe set _isConnected to true?
    this->_isConnected = true;

    this->_write(QString("NICK %1").arg(this->_nick));
    this->_write(QString("PASS %1").arg(this->_pass));
    this->_write("CAP REQ :twitch.tv/commands twitch.tv/tags");

    if (!this->_messageQueue.empty())
    {
        foreach (const QString& message, this->_messageQueue)
        {
            this->_write(message);
        }
    }
}

WebSocket* WebSocket::setNick(const QString& nick)
{
    this->_nick = nick;
    return this;
}

WebSocket* WebSocket::setPass(const QString& pass)
{
    this->_pass = (pass.startsWith("oauth:")) ? pass : "oauth:" + pass;
    return this;
}

WebSocket* WebSocket::setUrl(const QString& url)
{
    this->_url = QUrl(url);
    return this;
}

void WebSocket::sendRaw(const QString& text)
{
    // Socket ignores messages that we sent, if it hasn't emitted signal "connected"
    if (!this->_isConnected)
    {
        this->_messageQueue << text;
        return;
    }

    this->_write(text);
}

void WebSocket::connectToHost()
{
    this->_socket.open(this->_url);
}

}  // namespace EuleHakenBot
