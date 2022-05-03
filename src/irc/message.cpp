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
QString Message::getMainMsg()
{
    return this->mainMsg;
}
void Message::parse()
{
    if (this->rawMsg.isEmpty())
    {
        return;
    }
    QStringList buf = rawMsg.split(" ");
    if (buf.at(0) == "PING")
    {
        this->command = "PING";
        this->mainMsg = "PONG " + rawMsg;
    }
    else
    {
        //确保存在指令位
        if (buf.length() > 1)
        {
            this->command = buf.at(1);
        }
        else
        {
            this->command = "+";
            this->mainMsg = rawMsg;
        }
        //用foreach防止越界
        int count = 0;
        foreach (QString i, buf)
        {
            if (count > 2)
            {
                this->mainMsg += i + " ";
            }
            count++;
        }
    }
}