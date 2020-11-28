#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    action_taken_(false)
{
    ui->setupUi(this);
    Dialog* startDialog = new Dialog(this);
    startDialog->exec();

    qDebug() << "Window built";
    this->setFixedSize(width_ + 400, height_ + 200);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    timer = new QTimer();
    setTick(tick_);
    connect(timer, &QTimer::timeout, this, &MainWindow::advanceGame);

    //startti pitäs linkkaa oikein kellon kaa
    startbutton_ = new QPushButton("start", this);
    startbutton_->setGeometry(QRect(QPoint(100, 600), QSize(150, 70)));
    connect(startbutton_, &QPushButton::clicked, this, &MainWindow::on_startbutton_clicked);

    statistics_ = new statistics();

    QString picfile = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage pic(picfile);
    tre = std::make_shared<City>();
    tre.get()->setBackground(pic,pic);
    map->setBackgroundBrush(*tre.get()->getBackground());

    logic = std::make_shared<CourseSide::Logic>(this);
    logic.get()->takeCity(std::dynamic_pointer_cast<Interface::ICity>(tre));
    logic.get()->fileConfig();
    logic.get()->setTime(12,0);
    addGraphics();
    dude_ = new GraphicItem(250, 250, CHARACTER);
    //dude_ = std::make_shared<GraphicItem*>(cha);
    addActor(dude_);

    QShortcut* act = new QShortcut( QKeySequence("left"), this );
    connect(act, SIGNAL(activated()), this, SLOT(move_left()));
    QShortcut* act2 = new QShortcut( QKeySequence("right"), this );
    connect(act2, SIGNAL(activated()), this, SLOT(move_right()));
    QShortcut* act3 = new QShortcut( QKeySequence("up"), this );
    connect(act3, SIGNAL(activated()), this, SLOT(move_up()));
    QShortcut* act4 = new QShortcut( QKeySequence("down"), this );
    connect(act4, SIGNAL(activated()), this, SLOT(move_down()));
    point_info();
    show();

}

MainWindow::~MainWindow()
{
    // Remove graghics
    delete ui;
    delete timer;
}

void MainWindow::setTick(int t)
{
    timer->setInterval(t);
}

void MainWindow::addActor(GraphicItem *actorPic)
{
    map->addItem(actorPic);
    actors_.push_back(actorPic);
}

void MainWindow::addGraphics()
{
    std::map<std::shared_ptr<Interface::IStop>, GraphicItem*> stops = tre.get()->getStops();
    for(auto it = stops.begin(); it != stops.end(); ++it){
        map->addItem(it->second);
    }
    std::map<std::shared_ptr<Interface::IActor>, GraphicItem* > vehicles =
            tre.get()->getVehicles();
    qDebug() << vehicles.size();
    for(auto it = vehicles.begin(); it != vehicles.end(); ++it){
        bool in = false;
        for(auto iter = actors_.begin(); iter != actors_.end(); ++iter){
            if(*iter == it->second){
                in = true;
                break;
            }
        }
        if(!in){
            addActor(it->second);
        }
    }
    map->update();
}

void MainWindow::updateGraphics()
{

        std::vector<GraphicItem*> removed = tre.get()->getRemoved();
        for(auto it = removed.begin(); it != removed.end(); ++it){
            GraphicItem* n = *it;
            map->removeItem(n);
            delete n;
        }
        tre.get()->clearRemoved();

        std::map<std::shared_ptr<Interface::IActor>, GraphicItem* >  vehicles =
                tre.get()->getVehicles();
        for(auto it = vehicles.begin(); it != vehicles.end(); ++it){
            if(!inMap(it->second)){
                addActor(it->second);
            }
        }


}

void MainWindow::point_info()
{
    QString plane_amount = QString::number(statistics_->getPlanes());
    QString bus_amount = QString::number(statistics_->getBuses());
    QString point_amount = QString::number(statistics_->getPoints());

    ui->textBrowser->setText(" Current score: \n Planes caught:     " + plane_amount +
                             "\n Buses caught:      " + bus_amount + "\n Total points:        "
                             + point_amount);
}

void MainWindow::on_startbutton_clicked()
{
    logic->finalizeGameStart();
    addGraphics();
    timer->start();
    emit gameStarted();
    delete startbutton_;
}

void MainWindow::advanceGame()
{
    qDebug() << "advanceGame()";
    logic.get()->increaseTime();
    dude_->getcharacter().move(dude_->getcharacter().giveLocation());
    updateGraphics();
    map->update();
    point_info();
    action_taken_ = false;
}

void MainWindow::move_left()
{
    if(action_taken_ == false){
        action_taken_ = true;
        dude_->getcharacter().movement_commands("left");
    }
}

void MainWindow::move_right()
{
    if(action_taken_ == false){
        action_taken_ = true;
        dude_->getcharacter().movement_commands("right");
    }
}

void MainWindow::move_up()
{
    if(action_taken_ == false){
        action_taken_ = true;
        dude_->getcharacter().movement_commands("up");
    }
}

void MainWindow::move_down()
{
    if(action_taken_ == false){
        action_taken_ = true;
        dude_->getcharacter().movement_commands("down");
    }
}

bool MainWindow::inMap(GraphicItem * item)
{
    for(auto it = actors_.begin(); it != actors_.end(); ++it){
        if(*it == item){
            return true;
        }
        else if(*it == nullptr){
            actors_.erase(it);
        }
    }
    return false;
}
