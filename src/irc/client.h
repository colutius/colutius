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
    Message *sendMsg(Server *server, Channel *channel, QString msg);                    //发送消息
    //void rmServer(const QString serverName);                                            //删除服务器（通过名称）
    void rmServer(const int serverIndex);                                               //删除服务器（通过索引）
    //void rmServer(Server &server);                                                      //删除服务器（通过引用）
    //void rmChannel(Server &server, const QString channelName);                          //删除频道（通过引用服务器，频道名称）
    //void rmChannel(Server &server, const int channelIndex);                             //删除频道（通过引用服务器，频道索引）
    void rmChannel(const int serverIndex, const int channelIndex);                      //删除频道（通过服务器索引，频道索引）
};
