#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(Widget *widget, QSystemTrayIcon *parent)
{
    this->widget = widget;
    initTrayIcon();
    initConnect();
}
SystemTrayIcon::~SystemTrayIcon()
{
    config->deleteLater();
    start->deleteLater();
    exit->deleteLater();
    systemTrayIconMenu->deleteLater();
}
void SystemTrayIcon::initConnect()
{
    //添加系统托盘更新
    connect(this, &SystemTrayIcon::updateTrayIconSignal, this, &SystemTrayIcon::updateTrayIcon);
    //双击托盘关联
    connect(this, &SystemTrayIcon::activated, this, &SystemTrayIcon::showMainWidget);
    //退出
    connect(exit, &QAction::triggered, this, &SystemTrayIcon::OnExit);
    //显示配置界面
    connect(config, &QAction::triggered, this, &SystemTrayIcon::showConfigPage);
    //显示主界面
    connect(start, &QAction::triggered, this, &SystemTrayIcon::showMainWidget);
}
void SystemTrayIcon::initTrayIcon()
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

void SystemTrayIcon::OnExit()
{
    qApp->exit(0);
}

void SystemTrayIcon::showMainWidget()
{
    //显示主窗口
    widget->showNormal();
}
void SystemTrayIcon::updateTrayIcon()
{
    // TODO 从中间件获取服务器相应信息

    QString tipString = "Colutius-XXX\n当前频道数:";
    tipString += QString::number(widget->client->getServerNum());
    tipString += "\n当前服务数:";
    tipString += QString::number(10);
    tipString += "\n";
    this->setToolTip(tipString);
}

void SystemTrayIcon::showConfigPage()
{
    widget->config();
}
