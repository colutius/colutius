#include "client.h"
#include <QHostInfo>

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
    if (index < 0 || index >= getServerNum())
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
void Client::addServer(QString host, int port, QString nick, QString user, QString passwd)
{
    //构造新的服务器实例
    auto *newServer = new Server(host, port, nick, user, passwd);
    //添加到服务器列表
    this->serverList.append(newServer);
    //登录服务器
    if (newServer->login())
    {
        //发射登录成功信号
        qDebug() << "登录信息发送成功！";
        connect(newServer, &Server::success, this, [this]() { emit addServerSuccess(); });
        connect(newServer, &Server::fail, this, [this]() {
            this->serverList.removeLast();
            emit addServerFail();
        });
        connect(newServer, &Server::get, this, [this]() { emit getNewMessage(); });
        connect(newServer, &Server::channelAddSuccess, this, [this]() { emit addChannelSuccess(); });
        connect(newServer, &Server::channelAddFail, this, [this]() { emit addChannelFail(); });
    }
}
//添加频道
void Client::addChannel(const QString &channelName, int serverIndex)
{
    Server *server = getServer(serverIndex);
    server->addChannel(channelName);
}
//发送消息
Message *Client::sendMsg(Server *server, Channel *channel, QString msg)
{
    auto *message = new Message(MsgType::send);
    message->setrawMsg(msg);
    message->setNick(server->nick);
    message->setTFWhere(channel->getName());
    message->parseSend();
    if (message->getCommand() == "/msg")
    {
        server->sendData("PRIVMSG " + message->getTFWhere() + " :" + message->getMainMsg());
        server->addChannel(message->getTFWhere());
        return message;
    }
    else
    {
        server->sendData("PRIVMSG " + channel->getName() + " :" + message->getMainMsg());
        channel->addMessage(message);
        return message;
    }
}

void Client::rmServer(int serverIndex)
{
    if (!serverList.contains(getServer(serverIndex)))
    {
        return;
    }
    serverList.removeAt(serverIndex);
}

// void Client::rmChannel(Server &server, const int channelIndex) //需要重载Server的opterator==
//{
//     if (!serverList.contains(server))
//     {
//         return;
//     }
//     server.rmChannel(channelIndex);
// }

void Client::rmChannel(const int serverIndex, const int channelIndex)
{
    if (!serverList.contains(getServer(serverIndex)))
    {
        return;
    }
    serverList.at(serverIndex)->channelList.removeAt(channelIndex);
}
