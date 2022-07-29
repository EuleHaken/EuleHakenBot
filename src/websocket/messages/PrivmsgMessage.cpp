#include "PrivmsgMessage.hpp"

namespace EuleHakenBot {

PrivmsgMessage::PrivmsgMessage(IrcMessage& parent)
    : IrcMessage(parent)
{
    assert(parent.getCommand() == "PRIVMSG");

    this->_username = parent.getPrefix().split('!').constFirst();
    this->_channel = parent.getParams().constFirst();
    this->_message = parent.getParams().constLast();
}

const QString& PrivmsgMessage::getUsername() const
{
    return this->_username;
}

const QString& PrivmsgMessage::getChannel() const
{
    return this->_channel;
}

const QString& PrivmsgMessage::getMessage() const
{
    return this->_message;
}

}  // namespace EuleHakenBot
