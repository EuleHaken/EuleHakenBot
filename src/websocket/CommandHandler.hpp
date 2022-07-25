#pragma once

#include "messages/IrcMessage.hpp"

namespace EuleHakenBot {

class WebSocket;

class CommandHandler
{
public:
    virtual void handle(WebSocket& socket, IrcMessage& message) = 0;
};

}  // namespace EuleHakenBot
