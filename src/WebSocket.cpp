#include "WebSocket.hpp"

namespace EuleHakenBot {

WebSocket::WebSocket(QObject* parent)
    : QObject{parent}
    , _isConnected{false}
    , _defaultHandler{[](const IrcMessage&) {}}
    , _privmsgHandler{[](const PrivmsgMessage&) {}}
    , _pingHandler{[this](const IrcMessage& msg) {
        this->_defaultPingHandler(msg);
    }}
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

        //emit this->incomingMessage(IrcMessage::parse(line));

        IrcMessage parsedLine = IrcMessage::parse(line);
        QString command = parsedLine.getCommand();

        if (command == "PRIVMSG")
        {
            PrivmsgMessage privmsg = parsedLine;
            this->_privmsgHandler(privmsg);
        }
        else if (command == "PING")
        {
            this->_pingHandler(parsedLine);
        }
        else
        {
            this->_defaultHandler(parsedLine);
        }
    }
}

void WebSocket::_write(const QString& text)
{
    this->_socket.sendTextMessage(text);
    this->_socket.flush();
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

QWebSocket& WebSocket::getSocket()
{
    return this->_socket;
}

void WebSocket::connectToHost()
{
    this->_socket.open(this->_url);
}

/*
template <class T>
void WebSocket::registerCommandHandler(const WebSocketCommands command,
                                       void (*handler)(const T&))
{
    switch (command)
    {
        case WebSocketCommands::PING: {
            qInfo() << "Registered ping!";
            // convert to PingMessage, e.g.;
            break;
        }
        case WebSocketCommands::PRIVMSG: {
            this->_privmsgHandler = handler;
            auto i = {[](const T&) {}};
            break;
        }

        default: {
            qInfo() << "REGISTERED!!!";
            this->_defaultHandler = handler;
        }
    }
    //handler(IrcMessage::parse("@"));
}
*/

// ask, how we could put all of these setXXXHandler() methods to one method, e.g. registerHandler() with generics, e.g
void WebSocket::setDefaultCommandHandler(
    std::function<void(const IrcMessage&)> handler)
{
    this->_defaultHandler = handler;
}

void WebSocket::setPrivmsgHandler(
    std::function<void(const PrivmsgMessage&)> handler)
{
    this->_privmsgHandler = handler;
}

void WebSocket::_defaultPingHandler(const IrcMessage& message)
{
    QString reply = message.getRawMessage();
    this->_write(QString("PONG %1").arg(reply.remove("PING ")));
}

}  // namespace EuleHakenBot
