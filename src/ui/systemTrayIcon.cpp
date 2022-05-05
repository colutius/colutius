#include "systemTrayIcon.h"

systemTrayIcon::systemTrayIcon(Widget *widget, QSystemTrayIcon *parent)
{
    this->widget = widget;
    initTrayIcon();
    initConnect();
}
systemTrayIcon::~systemTrayIcon()
{
    max->deleteLater();
    min->deleteLater();
    systemTrayIconMenu->deleteLater();
    exit->deleteLater();
}
void systemTrayIcon::initConnect()
{
    //添加系统托盘更新
    connect(this, &systemTrayIcon::updateTrayIconSignal, this, &systemTrayIcon::updateTrayIcon);
    //双击托盘关联
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
    // ExitAction关联
    connect(exit, &QAction::triggered, this, &systemTrayIcon::OnExit);
    // MinAction关联
    connect(min, &QAction::triggered, this, [=] { widget->showMinimized(); });
    // MaxAction关联
    connect(max, &QAction::triggered, this, [=] { widget->showMaximized(); });
}
void systemTrayIcon::initTrayIcon()
{
    this->setIcon(QIcon(":/img/img/icon.png"));
    this->setToolTip("Colutius-XXX");
    this->show();

    //添加菜单
    systemTrayIconMenu = new QMenu();
    min = new QAction();
    exit = new QAction();
    max = new QAction();
    min->setText("最小化程序");
    exit->setText("退出");
    max->setText("最大化程序");
    //添加活动
    systemTrayIconMenu->addAction(min);
    systemTrayIconMenu->addAction(max);
    systemTrayIconMenu->addAction(exit);
    this->setContextMenu(systemTrayIconMenu);
}

void systemTrayIcon::OnExit()
{
    qApp->exit(0);
}

void systemTrayIcon::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
    {
        // 显示主窗口
        widget->showNormal();
    }
}
void systemTrayIcon::updateTrayIcon()
{
    // TODO 从中间件获取服务器相应信息

    QString tipString = "Colutius-XXX\n当前频道数:";
    tipString += QString::number(widget->client->getServerNum());
    tipString += "\n当前服务数:";
    tipString += QString::number(10);
    tipString += "\n";
    this->setToolTip(tipString);
}
