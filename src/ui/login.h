#pragma once

#include <QDialog>

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

  public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

  private:
    Ui::Login *ui;
};
