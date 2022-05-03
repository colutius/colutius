#include "config.h"
#include "ui_config.h"

Config::Config(QWidget *parent) : QDialog(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->setModal(true);
    this->show();
}

Config::~Config()
{
    delete ui;
}
