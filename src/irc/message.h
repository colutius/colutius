#pragma once

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
  public:
    QString rawMsg;  //原始数据
    QString command; //指令字段
    QString mainMsg; //主要信息
    explicit Message(QObject *parent = nullptr);
    ~Message() override;
    void setrawMsg(QString rawMsg); //设置原始数据
    QString getCommand();           //获取指令字段
    QString getMainMsg();           //获取主要信息
    void parse();                   //解析原始数据
};