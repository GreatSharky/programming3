#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(this, &Dialog::accepted, this, &Dialog::close);
}

Dialog::~Dialog()
{
    delete ui;
}
