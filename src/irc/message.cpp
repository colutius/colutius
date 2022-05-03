#include "message.h"

Message::Message(QObject *parent)
{
}
Message::~Message() = default;
//设置原始数据
void Message::setrawMsg(QString rawMsg)
{
    this->rawMsg = rawMsg;
}
//获取指令字段
QString Message::getCommand()
{
    return this->command;
}
