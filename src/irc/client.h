#pragma once

#include "channel.h"
#include "message.h"
#include "server.h"
#include <QDebug>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
  signals:
    void addServerSuccess();  //登录成功信号
    void addServerFail();     //登录失败信号
    void getNewMessage();     //受到新消息
    void addChannelSuccess(); //加入频道成功
    void addChannelFail();    //加入频道失败
  public:
    QList<Server *> serverList; //服务器列表

    explicit Client(QObject *parent = nullptr);
    ~Client() override;
    int getServerNum();                                                                 //获取服务器数量
    int getChannelNum(Server *server);                                                  //获取频道数量
    int getMessageNum(Channel *channel);                                                //获取消息数量
    Server *getServer(int index);                                                       //获取指定服务器对象
    Channel *getChannel(Server *server, int index);                                     //获取指定频道对象
    Message *getMessage(Channel *channel, int index);                                   //获取消息列表
    void addServer(QString host, int port, QString nick, QString user, QString passwd); //添加服务器
    void addChannel(const QString &channelName, int serverIndex);                       //添加频道
};