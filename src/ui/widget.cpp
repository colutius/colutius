#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    this->client = new Client;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/icon.svg"));
    initConnect();
}
Widget::~Widget()
{
    delete ui;
}
//初始化信号槽
void Widget::initConnect()
{
    //打开登陆页
    connect(ui->addServerBtn, &QPushButton::clicked, this, &Widget::login);
    //打开设置页
    connect(ui->settingBtn, &QPushButton::clicked, this, &Widget::config);
    //刷新服务器列表
    connect(this->client, &Client::addServerSuccess, this, &Widget::refreshServerList);
}
//打开登录对话框
void Widget::login()
{
    this->loginPage = new Login(this->client);
}
//打开设置对话框
void Widget::config()
{
    this->configPage = new Config;
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
    int count = ui->serverList->count();

    while (count--)
    {
        ui->serverList->takeItem(0);
    }

    for (int i = 0; i < client->getServerNum(); i++)
    {
        ui->serverList->addItem(client->getServer(i)->getItem());
    }
}
//刷新频道列表
void Widget::refreshChannelList()
{
}
//刷新消息列表
void Widget::refreshMessageList()
{
}
