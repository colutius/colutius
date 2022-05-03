#pragma once

#include "message.h"
#include <QDebug>
#include <QObject>

class Channel : public QObject
{
    Q_OBJECT
  public:
    QList<Message *> messageList; //消息列表

    explicit Channel(QObject *parent = nullptr);
    ~Channel() override;

    int getMessageNum();            //获取消息数量
    Message *getMessage(int index); //获取指定消息对象
};