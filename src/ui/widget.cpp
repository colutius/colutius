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
    //添加服务器成功
    connect(this->client, &Client::addServerSuccess, this, &Widget::addServerItem);
    //接收新消息
    connect(this->client, &Client::getNewMessage, this, &Widget::addMsg);
    //添加频道成功
    connect(this->client, &Client::addChannelSuccess, this, &Widget::addChannelItem);
    //添加频道失败
    connect(this->client, &Client::addChannelFail, this, &Widget::addChannelFail);
    //切换服务器
    connect(ui->serverList, &QListWidget::currentItemChanged, this, &Widget::refreshChannelList);
    //切换频道
    connect(ui->channelList, &QListWidget::currentItemChanged, this, &Widget::refreshMessageList);
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
//添加服务器对象
void Widget::addServerItem()
{
    ui->serverList->addItem(client->getServer(client->getServerNum() - 1)->getItem());
    ui->serverList->setCurrentRow(client->getServerNum() - 1);
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
//添加频道对象
void Widget::addChannelItem()
{
    ui->channelEdit->clear();
    Server *server = client->getServer(ui->serverList->currentRow());
    ui->channelList->addItem(client->getChannel(server, client->getChannelNum(server) - 1)->getItem());
    ui->channelList->setCurrentRow(client->getChannelNum(server) - 1);
}
//添加消息
void Widget::addMsg()
{
    Server *server = client->getServer(ui->serverList->currentRow());
    //如果当前频道列表为空，肯定不用处理
    if (ui->channelList->currentRow() == -1)
    {
        return;
    }
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
//刷新频道列表
void Widget::refreshChannelList()
{
    //暂时屏蔽信号，防止没有执行完毕时刷新消息列表导致索引出错
    ui->channelList->blockSignals(true);
    qDebug() << "刷新频道列表";
    int count = ui->channelList->count();

    while (count--)
    {
        ui->channelList->takeItem(0);
    }
    Server *server = client->getServer(ui->serverList->currentRow());
    for (int i = 0; i < client->getChannelNum(server); i++)
    {
        ui->channelList->addItem(client->getChannel(server, i)->getItem());
    }
    //解除屏蔽信号
    ui->channelList->blockSignals(false);
    ui->channelList->setCurrentRow(client->getChannelNum(server) - 1);
}
//刷新消息列表
void Widget::refreshMessageList()
{
    qDebug() << "刷新消息列表";
    int count = ui->msgList->count();

    while (count--)
    {
        ui->msgList->takeItem(0);
    }
    if (ui->channelList->currentRow() == -1)
    {
        return;
    }
    Server *server = client->getServer(ui->serverList->currentRow());
    Channel *channel = client->getChannel(server, ui->channelList->currentRow());
    for (int i = 0; i < client->getMessageNum(channel); i++)
    {
        ui->msgList->addItem(client->getMessage(channel, i)->getItem());
    }
}
//频道加入失败
void Widget::addChannelFail()
{
    QMessageBox::information(this, tr("频道加入失败"), tr("该频道只有注册用户可以加入！"));
}