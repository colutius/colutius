#pragma once

#include "../irc/client.h"
#include "config.h"
#include "login.h"
#include <QAction>
#include <QFile>
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

  public:
    Client *client;     //客户端对象
    Login *loginPage;   //登录页
    Config *configPage; //设置页
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;
    void initUI();             //初始化界面
    void initConnect();        //初始化信号槽
    void login();              //打开登录对话框
    void config();             //打开设置对话框
    void addChannel();         //添加频道
    void addMsg();             //添加消息
    void refreshChannelList(); //刷新频道列表
    void refreshMessageList(); //刷新消息列表
    void addChannelFail();     //添加频道失败
    void addServerItem();      //添加服务器
    void addChannelItem();     //添加频道
    void sendMsg();            //发送消息

  private:
    Ui::Widget *ui;
};
