#include "ui/systemTrayIcon.h"
#include "ui/widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false); //最后一个窗口关闭时，禁止退出应用程序
    Widget w;
    w.show();
    systemTrayIcon trayIcon(&w);
    trayIcon.show();
    return QApplication::exec();
}
