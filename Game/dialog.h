#ifndef DIALOG_H
#define DIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

namespace StudentSide {

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


signals:
    /**
     * @brief The signal that contains the name is sent to the mainwindow
     * @param The name of the player
     */
    void getname(QString name);

public slots:
    /**
     * @brief Emits the name as a signal
     */
    void giveName();

private:
    Ui::Dialog *ui;
    QString name_;
};
}

#endif // DIALOG_H
