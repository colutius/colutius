#pragma once

#include <QListWidgetItem>
#include <QObject>

class Message : public QObject
{
    Q_OBJECT
  public:
    QString nick;          //发送者昵称
    QString sender;        //消息发送者
    QString rawMsg;        //原始数据
    QString command;       //指令字段
    QString mainMsg;       //主要信息
    QListWidgetItem *item; //消息列表对象
    explicit Message(QObject *parent = nullptr);
    ~Message() override;
    void setrawMsg(QString rawMsg); //设置原始数据
    QListWidgetItem *getItem();     //获取消息列表对象
    QString getCommand();           //获取指令字段
    QString getSender();            //获取消息发送者
    QString getMainMsg();           //获取主要信息
    void parse();                   //解析原始数据
    void setSendMsg(QString msg, QString to, QString nick);
};