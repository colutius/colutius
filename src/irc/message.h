#pragma once

#include <QListWidgetItem>
#include <QObject>

enum MsgType
{
    receive = 0,
    send = 1
};
class Message : public QObject
{
    Q_OBJECT
  public:
    MsgType flag; //标志，0:收到的消息，1:发送的消息
    explicit Message(MsgType flag, QObject *parent = nullptr);
    ~Message() override;

    void setrawMsg(QString rawMsg); //设置原始数据
    void setNick(QString nick);     //设置昵称
    void setTFWhere(QString where); //设置消息去向/来源
    QListWidgetItem *getItem();     //获取消息列表对象
    QString getCommand();           //获取指令字段
    QString getTFWhere();           //获取消息去向/来源
    QString getMainMsg();           //获取主要信息
    QString getNick();              //获取昵称

    void parseReceive(); //解析接收到的原始数据
    void parseSend();    //解析即将发送的数据

  private:
    /* 共有字段 */
    QString _rawMsg;        //原始数据
    QString _mainMsg;       //主要信息
    QString _command;       //指令字段
    QString _nick;          //消息发送者昵称
    QListWidgetItem *_item; //消息列表对象
    /* 接收到消息独有字段 */
    QString _fromWhere; //消息来源 频道名称/发送者昵称
    /* 要发送消息独有字段 */
    QString _toWhere; //消息去向
};