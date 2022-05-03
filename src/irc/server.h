#pragma once

#include "channel.h"
#include <QDebug>
#include <QObject>
#include <QTcpSocket>
class Server : public QObject
{
    Q_OBJECT
  public:
    QList<Channel *> channelList; //频道列表
    QString host;                 //服务器地址
    int port;                     //端口号
    QString nick;                 //昵称
    QString user;                 //用户名
    QString passwd;               //密码
    QTcpSocket socket;            //连接对象
    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    int getChannelNum();               //获取频道数目
    Channel *getChannel(int index);    //获取指定频道对象
    int sendData(const QString &data); //发送数据
    bool login();                      //连接并登录服务器
};