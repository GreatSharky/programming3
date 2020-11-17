#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Window built";
    this->setFixedSize(height_,width_);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);


    QString picfile = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage pic(picfile);
    tre = std::make_unique<City>();
    tre.get()->setBackground(pic,pic);
    map->setBackgroundBrush(*tre.get()->getBackground());
    //tre.setBackground(pic,pic);
    //setPicture(*tre.getBackground());
    dataread_ = false;
    CourseSide::OfflineReader reader;
    data_ = reader.readFiles(BUSFILE,STOPFILE);
    qDebug() << "addInformation";
    dataread_ = addInformation();

    // Character voi toimii????
    // Häh - Aaro
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addActor(int locX, int locY, GraphicItems type)
{
    if(type == GraphicItems::STOP){
        StopGraphic *stop = new StopGraphic(locX, locY, type);
        actors_.push_back(stop);
        map->addItem(stop);
        last_ = stop;
    }
    else if(type == GraphicItems::BUS){
        SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
        actors_.push_back(nActor);
        map->addItem(nActor);
        last_ = nActor;
    }
    else if(type == NOTHING){
        SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
        actors_.push_back(nActor);
        map->addItem(nActor);
        last_ = nActor;
    }
}



bool MainWindow::addInformation()
{
    //add stops
    for(auto it = data_.get()->stops.begin(); it != data_.get()->stops.end();++it){
        tre.get()->addStop(*it);
        int x = it->get()->getLocation().giveX();
        int y = 500-it->get()->getLocation().giveY();
        addActor(x,y, STOP);
    }
    qDebug() << data_.get()->buses.size();
    int test = 0;
    for (auto it = data_.get()->buses.begin(); it != data_.get()->buses.end(); ++it) {
        std::shared_ptr<CourseSide::Nysse> bus = std::make_shared<CourseSide::Nysse>(it->get()->routeNumber);
        bus.get()->setRoute(it->get()->timeRoute2, it->get()->schedule.front()); // Not optimal time
        bus.get()->setSID(it->get()->routeId);

        tre.get()->addActor(bus);
        addActor(bus.get()->giveLocation().giveX(),bus.get()->giveLocation().giveY(), BUS);
        qDebug() << ++test;
    }
    return true;
}
