#include "ClearchatMessage.hpp"

namespace EuleHakenBot {

ClearchatMessage::ClearchatMessage(IrcMessage& parent)
    : IrcMessage(parent)
{
    assert(parent.getCommand() == "CLEARCHAT");

    this->_channel = parent.getParams().constFirst();
    this->_target = parent.getParams().constLast();
    this->_length = parent.getTags().value("ban-duration", "").toInt();

    bool isOk = false;
    int length = parent.getTags().value("ban-duration", "").toInt(&isOk);
    if (isOk)
    {
        this->_length = length;
    }
    else
        this->_length = -1;

    this->_isPermaban = this->_length == -1;
}

const QString& ClearchatMessage::getChannel() const
{
    return this->_channel;
}

/*
const QString& ClearchatMessage::getUser() const
{
    return this->_user;
}
*/

const QString& ClearchatMessage::getTarget() const
{
    return this->_target;
}

const bool ClearchatMessage::isPermaban() const
{
    return this->_isPermaban && this->_length == -1;
}

const int ClearchatMessage::getLength() const
{
    return this->_length;
}

}  // namespace EuleHakenBot
