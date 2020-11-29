#include "dialog.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    StudentSide::MainWindow w;

    return a.exec();
}
