#pragma once

#include "widget.h"
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

class systemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
  signals:
    void updateTrayIconSignal();

  public:
    Widget *widget;
    QMenu *systemTrayIconMenu;
    QAction *min;
    QAction *max;
    QAction *exit;
    explicit systemTrayIcon(Widget *widget, QSystemTrayIcon *parent = nullptr);
    ~systemTrayIcon() override;

    void initTrayIcon();
    void initConnect();
    void OnExit();
    void OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);
    void updateTrayIcon();
};
