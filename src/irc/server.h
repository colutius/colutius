#pragma once

#include "channel.h"
#include "message.h"
#include <QDebug>
#include <QFontDatabase>
#include <QHostInfo>
#include <QListWidgetItem>
#include <QObject>
#include <QRandomGenerator>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
  signals:
    void get();               //收到消息
    void success();           //服务器连接成功
    void fail();              //服务器连接失败
    void channelAddSuccess(); //频道加入成功
    void channelAddFail();    //频道加入失败

  public:
    QList<Channel *> channelList; //频道列表
    QList<QColor> colors;         //随机颜色列表
    QString host;                 //服务器地址
    int port;                     //端口号
    QString nick;                 //昵称
    QString user;                 //用户名
    QString passwd;               //密码
    QTcpSocket socket;            //连接对象

    QListWidgetItem *serverItem; //列表对象
    explicit Server(QString host, int port, QString nick, QString user, QString passwd, QObject *parent = nullptr);
    ~Server() override;
    void initConnect();                         //初始化信号槽
    void initItem();                            //初始化列表对象
    int getChannelNum();                        //获取频道数目
    void addChannel(const QString channelName); //添加频道
    Channel *getChannel(int index);             //获取指定频道对象
    QListWidgetItem *getItem();                 //获取列表对象
    int sendData(const QString &data);          //发送数据
    bool login();                               //连接并登录服务器
    void receiveData();                         //接收数据
};