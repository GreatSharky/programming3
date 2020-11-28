#ifndef DIALOG_H
#define DIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

namespace Aaro {

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


signals:
    void getname(QString name);

public slots:
    void giveName();

private:
    Ui::Dialog *ui;
    QString name_;
};
}

#endif // DIALOG_H
