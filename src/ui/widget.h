#pragma once

#include "../irc/client.h"
#include "config.h"
#include "login.h"
#include <QAction>
#include <QMenu>
#include <QString>
#include <QSystemTrayIcon>
#include <QWidget>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
  signals:
    void updateTrayIconSignal();

  public:
    Client *client;     //客户端对象
    Login *loginPage;   //登录页
    Config *configPage; //设置页
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

    void initConnect();        //初始化信号槽
    void login();              //打开登录对话框
    void config();             //打开设置对话框
    void addChannel();         //添加频道
    void addMsg();             //添加消息
    void refreshChannelList(); //刷新频道列表
    void refreshMessageList(); //刷新消息列表
    void initTrayIcon();       //初始化系统托盘
    void addChannelFail();     //添加频道失败
    void addServerItem();      //添加服务器
    void addChannelItem();     //添加频道
  public slots:
    void updateTrayIcon();                                             //更新系统托盘
    int OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason); //系统托盘事件
    int OnExit();                                                      //退出事件

  private:
    Ui::Widget *ui;
    QSystemTrayIcon *col_trayIcon; //系统托盘
    QMenu *systemTrayIconMenu;     //托盘菜单
    QAction *min;                  //最小化动作
    QAction *exit;                 //退出动作
    QAction *max;                  //最大化
};
