#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initConnect();
}
Widget::~Widget()
{
    delete ui;
}
//初始化信号槽
void Widget::initConnect()
{
    connect(ui->addServerBtn, &QPushButton::clicked, this, &Widget::login);
    connect(ui->settingBtn, &QPushButton::clicked, this, &Widget::config);
}
//打开登录对话框
void Widget::login()
{
    this->loginPage = new Login;
}
//打开设置对话框
void Widget::config()
{
    this->configPage = new Config;
}
//添加服务器
void Widget::addServer()
{
}
//添加频道
void Widget::addChannel()
{
}
//添加消息
void Widget::addMsg()
{
}
//切换服务器
void Widget::changeServer()
{
}
//切换频道
void Widget::changeChannel()
{
}
//刷新服务器列表
void Widget::refreshServerList()
{
}
//刷新频道列表
void Widget::refreshChannelList()
{
}
//刷新消息列表
void Widget::refreshMessageList()
{
}