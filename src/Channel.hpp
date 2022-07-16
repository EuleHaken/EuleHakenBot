#pragma once

#include <QDebug>
#include <QString>

namespace EuleHakenBot {

/**
 * @brief The Channel class represents a Twitch/IRC Channel
 */
class Channel
{
public:
    // Creates a new channel object
    // Will also create a new json file for this channel object
    Channel();

public:
    // We do this with callbacks, because we do network requests.
    // Maybe not the best way, but I can't think of a better way ATM
    void activeChatters(std::function<void(unsigned long)> cb);

    // void update(); to update emotes and so on, e.g. ?

private:
    QString _name;
    unsigned long _twitchID;
    QMap<QString, QStringList> _emotes;
};

}  // namespace EuleHakenBot
