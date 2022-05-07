#include "ui/systemTrayIcon.h"
#include "ui/widget.h"
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false); //最后一个窗口关闭时，禁止退出应用程序

    QSharedMemory shared("colutius");
    if (shared.attach())
    {
        QMessageBox::information(nullptr, "警告", "程序已经运行", QMessageBox::Yes);
        return  EXIT_SUCCESS;
    }
    shared.create(1);

    Widget w;
    w.show();
    systemTrayIcon trayIcon(&w);
    trayIcon.show();
    return QApplication::exec();
}
