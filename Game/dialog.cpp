#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(this, &Dialog::accepted, this, &Dialog::close);
    //connec(this, &Dialog::rejected, parent(mainwindow), &MainWindow::terminate)
}

Dialog::~Dialog()
{
    delete ui;
}
