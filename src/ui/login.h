#pragma once

#include "../irc/client.h"
#include <QDialog>

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

  public:
    Client *client;
    explicit Login(Client *client, QWidget *parent = nullptr);
    ~Login() override;

    void initConnect(); //初始化信号槽
    void addServer();   // 添加服务器
    void success();     //登陆成功
    void fail();        //登录失败

  private:
    Ui::Login *ui;
};
