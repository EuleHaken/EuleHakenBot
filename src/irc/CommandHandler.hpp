#pragma once

#include "irc/messages/IrcMessage.hpp"

#include <QWebSocket>

namespace EuleHakenBot {

class CommandHandler
{
public:
    virtual void handle(QWebSocket& socket, const IrcMessage& message) = 0;
};

}  // namespace EuleHakenBot

// TODO put everything, including socket and stuff into a seperate library on github!
