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

        emit this->incomingMessage(IrcMessage::parse(line));

        IrcMessage parsedLine = IrcMessage::parse(line);
        QString command = parsedLine.getCommand();

        if (command == "PING")
        {
            QString text = line.remove("PING ");
            this->_write(QString("PONG %1").arg(text));
            continue;
        }

        if (!this->_commandHandlers.contains(command))
            continue;

        //const auto& handlers = this->_commandHandlers[command];
        const auto& handlers = this->_commandHandlers.value(command);
        if (!handlers.empty())
        {
            foreach (const auto& handler, handlers)
            {
                handler->handle(*this, parsedLine);
            }
        }
    }
}

void WebSocket::_write(const QString& text)
{
    qInfo() << "WRITING: " << text;
    this->_socket.sendTextMessage(text);
    this->_socket.flush();
}

void WebSocket::onConnected()
{
    qInfo() << "connected!";
    this->_isConnected = true;

    this->_write(QString("PASS %1").arg(this->_pass));
    this->_write(QString("NICK %1").arg(this->_nick));
    this->_write("CAP REQ :twitch.tv/commands twitch.tv/tags");

    if (!this->_messageQueue.empty())
    {
        foreach (const QString& message, this->_messageQueue)
        {
            this->_write(message);
        }
    }
}

WebSocket& WebSocket::setNick(const QString& nick)
{
    this->_nick = nick;
    return *this;
}

WebSocket& WebSocket::setPass(const QString& pass)
{
    this->_pass = (pass.startsWith("oauth:")) ? pass : "oauth:" + pass;
    return *this;
}

WebSocket& WebSocket::setUrl(const QString& url)
{
    this->_url = QUrl(url);
    return *this;
}

void WebSocket::sendRaw(const QString& text)
{
    qInfo() << "WRITING RAW: " << text;

    // Socket ignores messages that we sent, if it hasn't emitted signal "connected"
    if (!this->_isConnected)
    {
        this->_messageQueue << text;
        return;
    }

    this->_write(text);
}

void WebSocket::sendMessage(const QString& channel, const QString& message)
{
    this->sendRaw(QString("PRIVMSG #%1 :%2").arg(channel).arg(message));
}

QWebSocket& WebSocket::getSocket()
{
    return this->_socket;
}

void WebSocket::connectToHost()
{
    this->_socket.open(this->_url);
}

void WebSocket::setHandler(const QString& command,
                           std::shared_ptr<CommandHandler> handler)
{
    if (this->_commandHandlers.contains(command))
    {
        this->_commandHandlers[command].append(handler);
    }
    else
    {
        QList<std::shared_ptr<CommandHandler>> list;
        list << handler;

        this->_commandHandlers.insert(command, list);
    }
}

void WebSocket::joinAll(const QStringList& channels)
{
    foreach (const QString& channel, channels)
    {
        this->sendRaw(QString("JOIN #%1").arg(channel));
    }
}

void WebSocket::join(const QString& channel)
{
    this->sendRaw(QString("JOIN #%1").arg(channel));
}

}  // namespace EuleHakenBot
