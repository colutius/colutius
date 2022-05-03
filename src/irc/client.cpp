#include "client.h"

Client::Client(QObject *parent)
{
}
Client::~Client() = default;
//获取服务器数量
int Client::getServerNum()
{
    return int(this->serverList.count());
}
//获取频道数量
int Client::getChannelNum(Server *server)
{
    return server->getChannelNum();
}
//获取消息数量
int Client::getMessageNum(Channel *channel)
{
    return channel->getMessageNum();
}
//获取指定服务器对象
Server *Client::getServer(int index)
{
    if (index < 0 || index > getServerNum())
    {
        qDebug() << "访问服务器列表索引超出范围！";
    }
    return this->serverList.at(index);
}
//获取指定频道对象
Channel *Client::getChannel(Server *server, int index)
{
    return server->getChannel(index);
}
//获取指定消息对象
Message *Client::getMessage(Channel *channel, int index)
{
    return channel->getMessage(index);
}

//添加服务器
void Client::addServer()
{
}
//添加频道
void Client::addChannel()
{
}
