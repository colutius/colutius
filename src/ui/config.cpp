#include "config.h"
#include "ui_config.h"

Config::Config(QWidget *parent) : QDialog(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->initUI();
    //设置模态对话框
    this->setModal(true);
    this->show();
}
void Config::initUI()
{
    //设置qss样式
    QFile qssFile(":/qss/qss/Config.qss");
    qssFile.open(QFile::ReadOnly);
    QString str = qssFile.readAll();
    this->setStyleSheet(str);
    //设置logo
    QImage logo;
    logo.load(":/img/img/icon.png");
    ui->logoLabel->setPixmap(QPixmap::fromImage(logo).scaled(100, 100));
}
Config::~Config()
{
    delete ui;
}
