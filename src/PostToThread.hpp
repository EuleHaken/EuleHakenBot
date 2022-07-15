#pragma once

#include <QCoreApplication>
#include <QEvent>

namespace EuleHakenBot {

// Borrowed from https://github.com/Chatterino/chatterino2/blob/master/src/util/PostToThread.hpp
template <typename F>
static void postToThread(F&& fun, QObject* obj = qApp)
{
    struct Event : public QEvent
    {
        using Fun = typename std::decay<F>::type;
        Fun fun;
        Event(Fun&& fun)
            : QEvent(QEvent::None)
            , fun(std::move(fun))
        {
        }
        Event(const Fun& fun)
            : QEvent(QEvent::None)
            , fun(fun)
        {
        }
        ~Event() override
        {
            fun();
        }
    };
    QCoreApplication::postEvent(obj, new Event(std::forward<F>(fun)));
}

}  // namespace EuleHakenBot
