#include "systemTrayIcon.h"

systemTrayIcon::systemTrayIcon(Widget *widget, QSystemTrayIcon *parent)
{
    this->widget = widget;
    initTrayIcon();
    initConnect();
}
systemTrayIcon::~systemTrayIcon()
{
    config->deleteLater();
    start->deleteLater();
    exit->deleteLater();
    systemTrayIconMenu->deleteLater();
}
void systemTrayIcon::initConnect()
{
    //添加系统托盘更新
    connect(this, &systemTrayIcon::updateTrayIconSignal, this, &systemTrayIcon::updateTrayIcon);
    //双击托盘关联
    connect(this, &systemTrayIcon::activated, this, &systemTrayIcon::showMainWidget);
    //退出
    connect(exit, &QAction::triggered, this, &systemTrayIcon::OnExit);
    //显示配置界面
    connect(config, &QAction::triggered, this, &systemTrayIcon::showConfigPage);
    //显示主界面
    connect(start, &QAction::triggered, this, &systemTrayIcon::showMainWidget);
}
void systemTrayIcon::initTrayIcon()
{
    this->setIcon(QIcon(":/img/img/icon.png"));
    this->setToolTip("Colutius-XXX");
    this->show();

    //添加菜单
    systemTrayIconMenu = new QMenu();
    config = new QAction();
    exit = new QAction();
    start = new QAction();
    start->setText("显示主界面");
    config->setText("配置");
    exit->setText("退出");
    //添加活动
    systemTrayIconMenu->addAction(start);
    systemTrayIconMenu->addAction(config);
    systemTrayIconMenu->addAction(exit);
    this->setContextMenu(systemTrayIconMenu);
}

void systemTrayIcon::OnExit()
{
    qApp->exit(0);
}

void systemTrayIcon::showMainWidget()
{
    //显示主窗口
    widget->showNormal();
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

void systemTrayIcon::showConfigPage()
{
    widget->config();
}
