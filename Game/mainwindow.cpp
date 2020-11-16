#include "mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent):
    CourseSide::SimpleMainWindow(parent)
{
    qDebug() << "Window built";
    QString picfile = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage pic(picfile);
    tre = std::make_unique<City>();
    tre.get()->setBackground(pic,pic);
    setPicture(*tre.get()->getBackground());
    //tre.setBackground(pic,pic);
    //setPicture(*tre.getBackground());
    dataread_ = false;
    CourseSide::OfflineReader reader;
    data_ = reader.readFiles(BUSFILE,STOPFILE);
    qDebug() << "addInformation";
    dataread_ = addInformation();
}

bool MainWindow::addInformation()
{
    //add stops
    for(auto it = data_.get()->stops.begin(); it != data_.get()->stops.end();++it){
        tre.get()->addStop(*it);
        addActor(it->get()->getLocation().giveX(),500-it->get()->getLocation().giveY());
    }
}
