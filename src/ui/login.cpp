#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    //设置模态对话框
    this->setModal(true);
    this->show();
}

Login::~Login()
{
    delete ui;
}
