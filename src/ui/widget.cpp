#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    this->client = new Client;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img/icon.svg"));
    initTrayIcon();
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
    //添加系统托盘更新
    connect(this, &Widget::updateTrayIconSignal, this, &Widget::updateTrayIcon);
    //双击托盘关联
    connect(col_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(OnSystemTrayClicked(QSystemTrayIcon::ActivationReason)));
    //ExitAction关联
    connect(exit, &QAction::triggered, this, &Widget::OnExit);
    //MinAction关联
    connect(min, &QAction::triggered, this, [=]{ this->showMinimized(); });
    //MaxAction关联
    connect(max, &QAction::triggered, this, [=]{ this->showMaximized(); });
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

/**
 * 初始化系统托盘
 * @brief Widget::initTrayIcon
 */
void Widget::initTrayIcon()
{
    col_trayIcon = new QSystemTrayIcon(this);
    col_trayIcon->setIcon(QIcon(":/img/img/icon.png"));
    col_trayIcon->setToolTip("Colutius-XXX");
    col_trayIcon->show();

    //添加菜单
    systemTrayIconMenu = new QMenu();
    min = new QAction();
    exit = new QAction();
    max = new QAction();
    min->setText("最小化程序");
    exit->setText("退出");
    max->setText("最大化程序");
    //添加活动
    systemTrayIconMenu->addAction(min);
    systemTrayIconMenu->addAction(max);
    systemTrayIconMenu->addAction(exit);
    col_trayIcon->setContextMenu(systemTrayIconMenu);
}

/**
 * 更新系统托盘信息
 * @brief Widget::updateTrayIcon
 * 更新数据 调用updateSystemTrayIconSignal 信号
 */
void Widget::updateTrayIcon()
{
    //TODO 从中间件获取服务器相应信息

    QString tipString = "Colutius-XXX\n当前频道数:";
    tipString += QString::number(client->getServerNum());
    tipString += "\n当前服务数:";
    tipString += QString::number(10);
    tipString += "\n";
    col_trayIcon->setToolTip(tipString);
}

/**
 * 系统托盘单双击事件
 * @brief Widget::OnSystemTrayClicked
 */
int Widget::OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
    {
        // 显示主窗口
        this->showNormal();
    }
    return 0;
}

/**
 * 程序退出事件
 * @brief Widget::OnExit
 * @return
 */
int Widget::OnExit()
{
    QApplication::exit(0);
    return 0;
}
