#include "channel.h"

Channel::Channel(QString name, QObject *parent)
{
    this->name = name;

    this->item = new QListWidgetItem(this->name);
}
Channel::~Channel() = default;
//获取频道名称
QString Channel::getName()
{
    return this->name;
}
//获取频道名称
QListWidgetItem *Channel::getItem()
{
    return this->item;
}
//获取消息数量
int Channel::getMessageNum()
{
    return int(this->messageList.count());
}
//获取指定消息对象
Message *Channel::getMessage(int index)
{
    if (index < 0 || index >= getMessageNum())
    {
        qDebug() << "消息索引超出范围！";
        return nullptr;
    }
    return this->messageList.at(index);
}
void Channel::addMessage(Message *msg)
{
    this->messageList.append(msg);
}
