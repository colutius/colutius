#include "channel.h"

Channel::Channel(QObject *parent)
{
}
Channel::~Channel() = default;
//获取消息数量
int Channel::getMessageNum()
{
    return int(this->messageList.count());
}
//获取指定消息对象
Message *Channel::getMessage(int index)
{
    if (index < 0 || index > getMessageNum())
    {
        qDebug() << "消息索引超出范围！";
        return nullptr;
    }
    return this->messageList.at(index);
}
