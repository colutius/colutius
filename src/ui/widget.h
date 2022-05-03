#pragma once

#include "../irc/client.h"
#include "config.h"
#include "login.h"
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

    void initConnect();        //初始化信号槽
    void login();              //打开登录对话框
    void config();             //打开设置对话框
    void addChannel();         //添加频道
    void addMsg();             //添加消息
    void changeServer();       //切换服务器
    void changeChannel();      //切换频道
    void refreshServerList();  //刷新服务器列表
    void refreshChannelList(); //刷新频道列表
    void refreshMessageList(); //刷新消息列表
  private:
    Ui::Widget *ui;
};
