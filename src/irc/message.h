#pragma once

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
  public:
    explicit Message(QObject *parent = nullptr);
    ~Message() override;
};