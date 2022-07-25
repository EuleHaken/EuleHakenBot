#pragma once

#include "IrcMessage.hpp"

namespace EuleHakenBot {

class ClearchatMessage final : public IrcMessage
{
public:
    ClearchatMessage(IrcMessage& parent);

public:
    const QString& getChannel() const;
    //const QString& getUser() const;
    const QString& getTarget() const;
    const bool isPermaban() const;
    const int getLength() const;

private:
    /**
     * @brief The channel where the `CLEARCHAT` was raised
     */
    QString _channel;

    /**
     * @brief The user who raised the `CLEARCHAT`
     *
     * Note: Actually not possible ATM :(
     */
    //QString _user;

    /**
     * @brief The target for the `CLEARCHAT`
     * For example, /ban {target}
     */
    QString _target;

    /**
     * @brief Wheter the `CLEARCHAT` was a permaban or not
     */
    bool _isPermaban{false};

    /**
     * @brief The length, for how long the `CLEARCHAT` should go on
     * -1 = permaban
     */
    int _length{-1};
};

}  // namespace EuleHakenBot
