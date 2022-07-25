#include "UsernoticeMessage.hpp"

namespace EuleHakenBot {

UsernoticeMessage::UsernoticeMessage(IrcMessage& parent)
    : IrcMessage(parent)
{
    assert(parent.getCommand() == "USERNOTICE");

    this->_channel = parent.getParams().constFirst();
    this->_message = parent.getParams().constLast();
    this->_user = parent.getTags().value("display-name", "");
    this->_target =
        parent.getTags().value("msg-param-recipient-display-name", "");

    // TODO add more, e.g. isPrime, streak/streakLength, isStreak, ... (see more in example_irc_messages.txt)
}

const QString& UsernoticeMessage::getChannel() const
{
    return this->_channel;
}

const QString& UsernoticeMessage::getMessage() const
{
    return this->_message;
}

const QString& UsernoticeMessage::getUser() const
{
    return this->_user;
}

const QString& UsernoticeMessage::getTarget() const
{
    return this->_target;
}

}  // namespace EuleHakenBot
