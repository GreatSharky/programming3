#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(height_,width_);
    Dialog* startDialog = new Dialog(this);
    startDialog->exec();

    qDebug() << "Window built";
    this->setFixedSize(height_ + 200, width_ + 200); // Lisäilin vähä

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    timer = new QTimer();
    setTick(tick_);
    connect(timer, &QTimer::timeout, this, &MainWindow::advanceGame);

    //startti pitäs linkkaa oikein kellon kaa
    startbutton_ = new QPushButton("start", this);
    startbutton_->setGeometry(QRect(QPoint(100, 600), QSize(50, 50)));
    connect(startbutton_, &QPushButton::clicked, this, &MainWindow::on_startbutton_clicked);

    QString picfile = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage pic(picfile);
    tre = std::make_shared<City>();
    tre.get()->setBackground(pic,pic);
    map->setBackgroundBrush(*tre.get()->getBackground());

    logic = std::make_shared<CourseSide::Logic>(this);
    logic.get()->takeCity(tre);
    logic.get()->fileConfig();
    logic.get()->setTime(12,0);
    logic->finalizeGameStart();
    addInformation();


    dude_ = new character(250, 250);
    addActor(dude_->giveLocation().giveX(), dude_->giveLocation().giveY(), NOTHING);
    // Täl voi ny piirtää grafiikat. tuli musta pallo näytöl
    show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTick(int t)
{
    timer->setInterval(t);
}

void MainWindow::addActor(int locX, int locY, GraphicItems type)
{
    if(type == GraphicItems::STOP){
        StopGraphic *stop = new StopGraphic(locX, locY, type);
        stops_.push_back(stop);
        map->addItem(stop);
        last_ = stop;
    }
    else if(type == GraphicItems::BUS){
        BusGraphic* nActor = new BusGraphic(locX, locY, type);
        vehicles_.push_back(nActor);
        map->addItem(nActor);
        last_ = nActor;
    }
    else if(type == NOTHING){
        SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
        stops_.push_back(nActor);
        map->addItem(nActor);
        last_ = nActor;
    }
}

bool MainWindow::addInformation()
{
    int x;
    int y;
    //add stops
    // auto iterator did not function fro these loops
    qDebug() << "Stops koko" << tre.get()->getStops().size();
    for(uint it = 0;it < tre.get()->getStops().size();++it){
        x = tre.get()->getStops()[it].get()->getLocation().giveX();
        y = 500-tre.get()->getStops()[it].get()->getLocation().giveY();
        addActor(x,y, STOP);
    }

    // add busses
    qDebug() << "Buses koko" << tre.get()->getBuses().size();
    for (uint it = 0; it < tre.get()->getBuses().size();++it) {
        x = tre.get()->getBuses()[it].get()->giveLocation().giveX();
        y = 500-tre.get()->getBuses()[it].get()->giveLocation().giveY();
        addActor(x, y, BUS);

    }
    return true;
}

void MainWindow::character_movement(QString command)
{
    dude_->movement_commands(command);
}

void MainWindow::on_startbutton_clicked()
{
    timer->start();
    emit gameStarted();
    delete startbutton_;
}

void MainWindow::advanceGame()
{
    qDebug() << "advanceGame()";
    logic.get()->advance();
    dude_->move(dude_->giveLocation());
    updateBuses();
}

void MainWindow::updateBuses()
{
    int x;
    int y;
    for (int it = 0; it < vehicles_.size(); ++it) {
        BusGraphic* bus = dynamic_cast<BusGraphic*>(vehicles_[it]);
        if(bus != nullptr){
            if(!tre.get()->getBuses()[it].get()->isRemoved()){
                x = tre.get()->getBuses()[it].get()->giveLocation().giveX();
                y = 500 - tre.get()->getBuses()[it].get()->giveLocation().giveY();
                bus->updateGraphic(x,y);
            }
            else{
                // removes removed vechile
                vehicles_.erase(vehicles_.begin()+it-1);
            }
        }
    }
}
