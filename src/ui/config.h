#pragma once

#include <QDialog>
#include <QFile>

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

    void initUI();

  private:
    Ui::Config *ui;
};
