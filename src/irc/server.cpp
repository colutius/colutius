#include "server.h"

QChar getFontID(QChar letter);
Server::Server(QString host, int port, QString nick, QString user, QString passwd, QObject *parent)
{

    this->host = host;
    this->port = port;
    this->nick = nick;
    this->user = user;
    this->passwd = passwd;

    //初始化服务器图标随机颜色列表
    this->colors.append(QColor(0xdcff93));
    this->colors.append(QColor(0xff9b6a));
    this->colors.append(QColor(0xf1b8e4));
    this->colors.append(QColor(0xd9b8f1));
    this->colors.append(QColor(0xb8f1ed));
    this->colors.append(QColor(0xf3d64e));
    this->colors.append(QColor(0xf1ccb8));
    this->colors.append(QColor(0xed9678));
    initConnect();
    initItem();
}
Server::~Server() = default;
//初始化信号槽
void Server::initConnect()
{
    //接收数据
    connect(&this->socket, &QTcpSocket::readyRead, this, &Server::receiveData);
    //加入失败时从列表中删除频道
    connect(this, &Server::channelAddFail, this, [this]() { this->channelList.removeLast(); });
}
//初始化item对象
void Server::initItem()
{
    //初始化item实例
    this->serverItem = new QListWidgetItem;
    serverItem->setToolTip("地址:" + this->host + "\n" + "昵称:" + this->nick);
    //初始化字母字体
    int fontId = QFontDatabase::addApplicationFont(":/font/iconfont/letter.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    const auto &fontName = fontFamilies.at(0);
    QFont letterFont;
    letterFont.setFamily(fontName);
    letterFont.setPointSize(40);
    this->serverItem->setFont(letterFont);
    //设置server图标
    QStringList name = this->host.split(".");
    this->serverItem->setText(getFontID(name.at(1)[0]));
    //设置随机颜色
    this->serverItem->setForeground(this->colors.at(QRandomGenerator::global()->generate() % colors.length()));
}
//获取频道数目
int Server::getChannelNum()
{
    return int(this->channelList.count());
}
//添加频道
void Server::addChannel(const QString channelName)
{
    //没有#说明是私信，不需要join
    if (channelName[0] != '#')
    {
        auto *newChannel = new Channel(channelName);
        this->channelList.append(newChannel);
        emit channelAddSuccess();
    }
    else
    {
        if (this->sendData("JOIN " + channelName))
        {
            qDebug() << "加入频道指令发送成功";
            auto *newChannel = new Channel(channelName);
            this->channelList.append(newChannel);
        }
    }
}
//获取指定频道对象
Channel *Server::getChannel(int index)
{
    if (index < 0 || index >= getChannelNum())
    {
        qDebug() << "频道索引超出范围";
    }
    return this->channelList.at(index);
}
//获取列表对象
QListWidgetItem *Server::getItem()
{
    return this->serverItem;
}
//发送数据
int Server::sendData(const QString &data)
{
    QByteArray buf = (data + "\r\n").toUtf8();
    return int(this->socket.write(buf));
}
//连接并登录服务器
bool Server::login()
{
    //连接到服务器
    socket.connectToHost(this->host, this->port);
    qDebug() << "连接成功！";
    //登录
    if (!this->passwd.isEmpty())
    {
        if (!sendData("PASS " + this->passwd))
        {
            return false;
        }
    }
    if (sendData("NICK " + this->nick))
    {
        if (sendData("User " + this->user + " 8 * :Colutius IRC Client"))
        {
            return true;
        }
    }
    return false;
}
//接收数据
void Server::receiveData()
{
    QString data = this->socket.readAll();
    QStringList buf = data.split("\r\n");
    foreach (QString i, buf)
    {
        if (!i.isEmpty())
        {
            //新建消息实例
            auto msg = new Message;
            //设置原始数据
            msg->setrawMsg(i);
            //解析消息
            msg->parse();
            if (msg->sender == this->nick)
            {
                msg->sender = msg->nick;
            }
            //回应PING
            if (msg->getCommand() == "PING")
            {
                this->sendData(msg->getMainMsg());
                qDebug() << "PING? PONG!";
            }
            else if (msg->getCommand() == "376")
            {
                qDebug() << "登录成功！";
                emit success();
            }
            else if (msg->getCommand() == "433")
            {
                qDebug() << "登录失败！昵称被占用！";
                emit fail();
            }
            else if (msg->getCommand() == "ERROR")
            {
                qDebug() << "登录失败！";
                emit fail();
            }
            else if (msg->getCommand() == "PRIVMSG")
            {
                qDebug() << "接收到一条用户消息";
#ifdef __linux__
                QString notify = "notify-send '" + msg->getSender() + "'  '" + msg->getMainMsg() + "' " + "-t 10000";
                system(notify.toStdString().data());
#elif __WIN32__
// windows 系统通知
#endif
                foreach (Channel *channel, this->channelList)
                {
                    if (msg->getSender() == channel->getName())
                    {
                        qDebug() << channel->getName() + "频道收到新消息";
                        channel->addMessage(msg);
                        emit get();
                        return;
                    }
                }
                //能执行到这儿说明是陌生人的消息
                this->addChannel(msg->getSender());
                qDebug() << this->getChannel(this->getChannelNum() - 1)->getName() + "频道收到新消息";
                this->getChannel(this->getChannelNum() - 1)->addMessage(msg);
                emit get();
            }
            else if (msg->getCommand() == "366")
            {
                qDebug() << "频道加入成功！";
                emit channelAddSuccess();
            }
            else if (msg->getCommand() == "477")
            {
                qDebug() << "频道加入失败，该频道只有注册用户可以加入！";
                emit channelAddFail();
            }
            else
            {
                qDebug() << msg->getCommand() + " " + msg->getMainMsg();
            }
        }
    }
}
//获取字母对应图标ID
QChar getFontID(QChar letter)
{
    switch (letter.unicode())
    {
    case u'a':
        return QChar(0xeb87);
    case u'b':
        return QChar(0xeb88);
    case u'c':
        return QChar(0xeb85);
    case u'd':
        return QChar(0xeb86);
    case u'e':
        return QChar(0xeb8a);
    case u'f':
        return QChar(0xeb89);
    case u'g':
        return QChar(0xeb8b);
    case u'h':
        return QChar(0xeb8d);
    case u'i':
        return QChar(0xeb8c);
    case u'j':
        return QChar(0xeb8e);
    case u'k':
        return QChar(0xeb97);
    case u'l':
        return QChar(0xeb8f);
    case u'm':
        return QChar(0xeb93);
    case u'n':
        return QChar(0xeb91);
    case u'o':
        return QChar(0xeb90);
    case u'p':
        return QChar(0xeb92);
    case u'q':
        return QChar(0xeb95);
    case u'r':
        return QChar(0xeb96);
    case u's':
        return QChar(0xeb9f);
    case u't':
        return QChar(0xeb98);
    case u'u':
        return QChar(0xeb9b);
    case u'v':
        return QChar(0xeb99);
    case u'w':
        return QChar(0xeb9a);
    case u'x':
        return QChar(0xeb9e);
    case u'y':
        return QChar(0xeb9d);
    case u'z':
        return QChar(0xeb9c);
    default:
        return QChar(0xeb94);
    }
}