#pragma once

#include "IrcMessage.hpp"

namespace EuleHakenBot {

class PrivmsgMessage final : public IrcMessage
{
public:
    PrivmsgMessage(IrcMessage& parent);

public:
    const QString& getUsername() const;
    const QString& getChannel() const;
    const QString& getMessage() const;

private:
    QString _username;
    QString _channel;
    QString _message;
};

}  // namespace EuleHakenBot
