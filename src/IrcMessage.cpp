#include "IrcMessage.hpp"

namespace EuleHakenBot
{

IrcMessage::IrcMessage(const QString& rawMsg,
                                     const QString& prefix,
                                     const QString& command,
                                     const QStringList& params,
                                     const QMap<QString, QString>& tags)
    : _rawMessage(rawMsg)
    , _prefix(prefix)
    , _command(command)
    , _params(params)
    , _tags(tags)
{
}

IrcMessage::IrcMessage()
    : _rawMessage("")
    , _prefix("")
    , _command("")
    , _params(QStringList())
    , _tags(QMap<QString, QString>())
{
}

const QString & IrcMessage::getRawMessage() const
{
    return this->_rawMessage;
}

const QString&IrcMessage::getPrefix() const
{
    return this->_prefix;
}

const QString &IrcMessage::getCommand() const{
    return this->_command;
}

const QStringList& IrcMessage::getParams() const  {
    return this->_params;
}

const QMap<QString, QString>& IrcMessage::getTags() const
{
    return this->_tags;
}

const IrcMessage IrcMessage::parse(
    const QString& text)
{
    QString prefix, command;
    QStringList params;
    QMap<QString, QString> tags;

    int pos{0};
    int nextSpace{0};

    if (text.at(pos) == '@')
    {
        nextSpace = text.indexOf(' ');

        if (nextSpace == -1)
        {
            qWarning() << "Malformed IRC message!";
            return IrcMessage{};
        }

        QString substringMsg(text.mid(1, nextSpace));
        QStringList splitMsg = substringMsg.split(';');

        foreach (QString keyValue, splitMsg)
        {
            QString key, val;

            QStringList keyValueSplit = keyValue.split('=');

            if (keyValueSplit.length() <= 1)
            {
                key = keyValueSplit.at(0);
                val = "";
            }
            else
            {
                key = keyValueSplit.at(0);
                val = keyValueSplit.at(
                    1);  // TODO I think we should check if keyValueSplit[0|1] contains whitespace at end, if so, trim i using .trimmed() method.
            }

            tags.insert(key, val);
        }

        pos = nextSpace + 1;
    }

    auto debugFirst = text.at(pos);
    while (debugFirst == ' ')
        pos++;

    auto debugSec = text.at(pos);
    if (debugSec == ':')
    {
        nextSpace = text.indexOf(' ', pos);

        if (nextSpace == -1)
        {
            return IrcMessage{};
        }

        prefix = text.mid(pos + 1, nextSpace - (pos + 1));
        pos = nextSpace + 1;

        while (text.at(pos) == ' ')
            pos++;
    }

    nextSpace = text.indexOf(' ', pos);

    if (nextSpace == -1)
    {
        if (text.length() > pos)
            command = text.right(text.length() - pos);
    }
    else
    {
        command = text.mid(pos, nextSpace - pos);
        pos = nextSpace + 1;

        while (text.at(pos) == ' ')
            pos++;

        while (pos < text.length())
        {
            nextSpace = text.indexOf(' ', pos);

            if (text.at(pos) == ':')
            {
                QString appendText = text.right(text.length() - (pos + 1));
                if (!appendText.isEmpty())
                    params.append(text.right(text.length() - (pos + 1)));

                break;
            }

            if (nextSpace != -1)
            {
                params.append(text.mid(pos, nextSpace));
                pos = nextSpace + 1;

                while (text.at(pos) == ' ')
                    pos++;

                continue;
            }

            if (nextSpace == -1)
            {
                params.append(text.right(text.length() - pos));
                break;
            }
        }

        QString nameParam = params.at(0);
        if (!nameParam.isEmpty())
        {
            int nameParamWhitespaceIndex = nameParam.indexOf(' ');
            params.replace(0, nameParam.left(nameParamWhitespaceIndex));
        }
    }

    return IrcMessage(text, prefix, command, params, tags);
}

} // namespace EuleHakenBot
