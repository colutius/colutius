#include "server.h"

Server::Server(QObject *parent)
{
}
Server::~Server() = default;
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
    //登录
    if (sendData("NICK " + this->nick))
    {
        if (sendData("User " + this->user))
        {
            return true;
        }
    }
    return false;
}
