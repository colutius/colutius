/**
 * 聊天气泡框架
 * @author Dthree
 * @date 22.5.5
 */
#ifndef BOCHATWIDGET_H
#define BOCHATWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class BoChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoChatWidget(QWidget *parent = nullptr);

signals:

};

#endif // BOCHATWIDGET_H
