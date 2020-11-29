#include "dialog.h"
#include "ui_dialog.h"

using namespace StudentSide;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(this, &Dialog::accepted, this, &Dialog::giveName);
    connect(this, &Dialog::accepted, this, &Dialog::close);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::giveName()
{
    emit getname(ui->lineEdit->text());
}
