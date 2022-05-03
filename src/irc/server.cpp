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

    initItem();
}
Server::~Server() = default;

void Server::initItem()
{
    //初始化item实例
    this->serverItem = new QListWidgetItem;
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
//获取指定频道对象
Channel *Server::getChannel(int index)
{
    if (index < 0 || index > getChannelNum())
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
            qDebug() << "登陆成功！";
            return true;
        }
    }
    return false;
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