#include "mainwindow.h"


Aaro::MainWindow::MainWindow(QWidget *parent):
    CourseSide::SimpleMainWindow(parent)
{
    setSize(1000,1000);
    QString picfile = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QImage pic(picfile);
    setPicture(pic);
}
