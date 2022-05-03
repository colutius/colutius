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
    //添加频道
    connect(ui->addChannelBtn, &QPushButton::clicked, this, &Widget::addChannel);
    //刷新服务器列表
    connect(this->client, &Client::addServerSuccess, this, &Widget::refreshServerList);
    //接收新消息
    connect(this->client, &Client::getNewMessage, this, &Widget::addMsg);
    //添加频道成功
    connect(this->client, &Client::addChannelSuccess, this, &Widget::refreshChannelList);
    //添加频道失败
    connect(this->client, &Client::addChannelFail, this,
            [this]() { QMessageBox::information(this, tr("频道加入失败"), tr("该频道只有注册用户可以加入！")); });
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
    //无服务器啥也不做
    if (!client->getServerNum())
    {
        return;
    }
    //获取频道名称
    QString channel = ui->channelEdit->text();
    //输入框为空啥也不做
    if (channel.isEmpty())
    {
        return;
    }
    //获取当前选中服务器
    int serverIndex = ui->serverList->currentRow();
    //发送JOIN信号
    client->addChannel(channel, serverIndex);
}
//添加消息
void Widget::addMsg()
{
    Server *server = client->getServer(ui->serverList->currentRow());
    Channel *channel = client->getChannel(server, ui->channelList->currentRow());
    int count = ui->msgList->count();
    //数量没变说明是其他频道的消息，不需要处理
    if (channel->getMessageNum() == count)
    {
        return;
    }
    else
    {
        ui->msgList->addItem(channel->getMessage(channel->getMessageNum() - 1)->getItem());
    }
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
        ui->serverList->setCurrentItem(client->getServer(i)->getItem());
    }
}
//刷新频道列表
void Widget::refreshChannelList()
{
    ui->channelEdit->clear();
    int count = ui->channelList->count();

    while (count--)
    {
        ui->channelList->takeItem(0);
    }

    Server *server = client->getServer(ui->serverList->currentRow());

    for (int i = 0; i < client->getChannelNum(server); i++)
    {
        ui->channelList->addItem(client->getChannel(server, i)->getItem());
        ui->channelList->setCurrentItem(client->getChannel(server, i)->getItem());
    }
}
//刷新消息列表
void Widget::refreshMessageList()
{
}
