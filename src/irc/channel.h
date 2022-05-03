#pragma once

#include "message.h"
#include <QDebug>
#include <QObject>

class Channel : public QObject
{
    Q_OBJECT
  public:
    QList<Message *> messageList; //消息列表
    QString name;                 //频道名称
    QListWidgetItem *item;        //列表项目
    explicit Channel(QString name, QObject *parent = nullptr);
    ~Channel() override;

    QString getName();              //获取频道名称
    QListWidgetItem *getItem();     //获取列表对象
    int getMessageNum();            //获取消息数量
    Message *getMessage(int index); //获取指定消息对象
    void addMessage(Message *msg);  //添加消息
};