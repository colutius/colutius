#pragma once

#include "widget.h"
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
  signals:
    void updateTrayIconSignal();

  public:
    Widget *widget;
    QMenu *systemTrayIconMenu;
    QAction *config;
    QAction *exit;
    QAction *start;
    explicit SystemTrayIcon(Widget *widget, QSystemTrayIcon *parent = nullptr);
    ~SystemTrayIcon() override;

    void initTrayIcon();   //初始化托盘图标
    void initConnect();    //初始化信号槽
    void OnExit();         //退出程序
    void showMainWidget(); //显示主界面
    void updateTrayIcon(); //更新托盘图标
    void showConfigPage(); //显示配置界面
};
