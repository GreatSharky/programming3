#include "mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent):
    CourseSide::SimpleMainWindow(parent)
{
    setSize(10000,10000);
    QString picfile = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";
    QImage pic(picfile);
    std::shared_ptr<City> tre = std::make_shared<City>();
    tre.get()->setBackground(pic,pic);
    setPicture(*tre.get()->getBackground());
}
