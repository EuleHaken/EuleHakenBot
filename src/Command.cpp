#include "Command.hpp"

namespace EuleHakenBot {

Command::Command(const QString& name, const CodeFunc& code, int cooldown,
                 const QString& description)
    : _name{name}
    , _code{code}
    , _cooldown{cooldown}
    , _description{description}
{
}

}  // namespace EuleHakenBot
