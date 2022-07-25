#pragma once

#include <QString>
#include <functional>

namespace EuleHakenBot {

using CodeFunc = std::function<QString()>;

class Command
{
    Q_DISABLE_COPY(Command)

protected:
    Command() = delete;
    Command(const QString& name, const CodeFunc& code, const int& cooldown,
            const QString& description);

protected:
    QString _name;
    CodeFunc _code;
    int _cooldown;
    QString _description;
};

}  // namespace EuleHakenBot
