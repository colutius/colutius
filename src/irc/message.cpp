#include "message.h"

Message::Message(MsgType flag, QObject *parent) : QObject(parent)
{
    this->flag = flag;
}
Message::~Message() = default;
//设置原始数据
void Message::setrawMsg(QString rawMsg)
{
    this->_rawMsg = rawMsg;
}
//设置消息去向/来源
void Message::setTFWhere(QString where)
{
    if (this->flag == receive)
    {
        this->_fromWhere = where;
    }
    if (this->flag == send)
    {
        this->_toWhere = where;
    }
}
//设置昵称
void Message::setNick(QString nick)
{
    this->_nick = nick;
}
//获取指令字段
QString Message::getCommand()
{
    return this->_command;
}
//获取主要信息
QString Message::getMainMsg()
{
    return this->_mainMsg;
}
//获取消息来源/去向
QString Message::getTFWhere()
{
    switch (this->flag)
    {
    case receive:
        return this->_fromWhere;
    case send:
        return this->_toWhere;
    }
    return QString();
}
//获取昵称
QString Message::getNick()
{
    return this->_nick;
}
//获取消息对象
QListWidgetItem *Message::getItem()
{
    return this->_item;
}
//解析接收信息
void Message::parseReceive()
{
    //原始数据为空不做处理
    if (this->_rawMsg.isEmpty())
    {
        return;
    }
    //原始数据按空格分隔
    QStringList buf = _rawMsg.split(" ");
    //指令位在第一位的情况
    // PING消息
    if (buf.at(0) == "PING")
    {
        this->_command = "PING";
        this->_mainMsg = _rawMsg.replace("PING", "PONG");
    }
    // ERROR信息
    else if (buf.at(0) == "ERROR")
    {
        this->_command = "ERROR";
        this->_mainMsg = _rawMsg;
    }
    //指令位在第二位的情况
    else
    {
        //确保存在指令位
        if (buf.length() > 1)
        {
            this->_command = buf.at(1);
        }
        //处理意外的换行
        else
        {
            this->_command = "+";
            this->_mainMsg = _rawMsg;
        }
        //获取主要信息
        int count = 0;
        foreach (QString i, buf)
        {
            if (count > 2)
            {
                this->_mainMsg += i + " ";
            }
            count++;
        }
        //如果是收到的用户信息，构造界面消息
        if (this->_command == "PRIVMSG")
        {
            setTFWhere(buf[2]);
            setNick(buf[0].split("!")[0].remove(":"));
            this->_item = new QListWidgetItem("[" + this->_nick + "]-> " + this->_mainMsg);
        }
    }
}
//解析发送消息
void Message::parseSend()
{
    //原始数据按空格分隔
    QStringList buf = this->_rawMsg.split(" ");
    //判断是否为指令信息
    if (buf[0] == "/msg")
    {
        this->_command = "/msg";
        setTFWhere(buf[1]);
        //获取主要信息
        int count = 0;
        foreach (QString i, buf)
        {
            if (count > 1)
            {
                this->_mainMsg += i + " ";
            }
            count++;
        }
        //构造界面显示信息
        this->_item = new QListWidgetItem(this->_mainMsg + " <-[" + this->_nick + "]");
    }
    //发送普通消息
    else
    {
        //普通消息可直接发送
        this->_mainMsg = this->_rawMsg;
        //构造界面显示信息
        this->_item = new QListWidgetItem(this->_mainMsg + " <-[" + this->_nick + "]");
        //发送消息右对齐
        this->_item->setTextAlignment(2);
    }
}
