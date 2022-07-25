#pragma once

#include "IrcMessage.hpp"

#include <QString>

namespace EuleHakenBot {

class UsernoticeMessage final : public IrcMessage
{
public:
    UsernoticeMessage(IrcMessage& parent);

public:
    const QString& getChannel() const;
    const QString& getMessage() const;
    const QString& getUser() const;
    const QString& getTarget() const;
    const QString& getType() const;

private:
    /**
     * @brief The channel where the `USERNOTICE` was raised
     */
    QString _channel;

    /**
     * @brief The message, that was sent with the `USERNOTICE`
     * This could be a user subscribing to a channel and also sending a
     * message.
     */
    QString _message;

    /**
     * @brief The user that raised the `USERNOTICE`
     */
    QString _user;

    /**
     * @brief The target that the `USERNOTICE` goes to
     * This could be someone gifting another user a subscription
     */
    QString _target;

    /**
     * @brief The type of the notice. E.g. subscription, announcement, ...
     */
    QString _type;
};

}  // namespace EuleHakenBot
