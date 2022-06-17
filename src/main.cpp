#include "MainWindow.hpp"
#include "Response.hpp"

#include <QApplication>
#include <QDebug>

using namespace EuleHakenBot;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Response res = Response();
    bool s = res.isFailure();

    return a.exec();
}
