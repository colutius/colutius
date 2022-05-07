#pragma once

#include "message.h"
#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QObject>

class Channel : public QObject
{
    Q_OBJECT
  public:
    QAction *part;
    QMenu *menu;
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

    bool operator == (const Channel &channel) //根据频道名称来区别不同频道
    {
        if (this->name == channel.name)
        {
            return true;
        }
        return false;
    };
};
