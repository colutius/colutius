#include "login.h"
#include "ui_login.h"

Login::Login(Client *client, QWidget *parent) : QDialog(parent), ui(new Ui::Login)
{
    //关闭对话框时调用析构函数
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->client = client;
    ui->setupUi(this);
    initConnect();
    //设置模态对话框
    this->setModal(true);
    this->show();
}

Login::~Login()
{
    delete ui;
}

void Login::initConnect()
{
    //点击连接
    connect(ui->connectBtn, &QPushButton::clicked, this, &Login::addServer);
    //登录成功
    connect(this->client, &Client::addServerSuccess, this, &Login::success);
    //登录失败
    connect(this->client, &Client::addServerFail, this, &Login::fail);
}
void Login::addServer()
{
    ui->connectBtn->setEnabled(false);
    //获取用户输入
    QString host = ui->hostEdit->text();
    QString port = ui->portEdit->text();
    QString nick = ui->nickEdit->text();
    QString user = ui->userEdit->text();
    QString passwd = ui->passwdEdit->text();
    if (host.isEmpty() || port.isEmpty() || nick.isEmpty() || user.isEmpty())
    {
        qDebug() << "输入信息不完整";
        ui->connectBtn->setEnabled(true);
    }
    client->addServer(host, port.toInt(), nick, user, passwd);
}
//登录成功
void Login::success()
{
    this->close();
}

void Login::fail()
{
    ui->connectBtn->setEnabled(true);
    QMessageBox::information(this, tr("登录失败"), tr("昵称被占用！"));
}