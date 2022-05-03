#pragma once

#include <QDialog>

namespace Ui
{
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

  public:
    explicit Config(QWidget *parent = nullptr);
    ~Config() override;

  private:
    Ui::Config *ui;
};
