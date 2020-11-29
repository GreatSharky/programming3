#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace StudentSide;

StudentSide::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    action_taken_(false)
{
    ui->setupUi(this);

    qDebug() << "Window built";
    this->setFixedSize(width_ + 300, height_ + 20);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    timer = new QTimer();
    setTick(tick_);
    connect(timer, &QTimer::timeout, this, &MainWindow::advanceGame);

    startbutton_ = new QPushButton("start", this);
    startbutton_->setGeometry(QRect(QPoint(530, 420), QSize(256, 80)));
    connect(startbutton_, &QPushButton::clicked, this, &MainWindow::on_startbutton_clicked);

    createClock();

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

    QShortcut* act = new QShortcut( QKeySequence("left"), this );
    connect(act, SIGNAL(activated()), this, SLOT(move_left()));
    QShortcut* act2 = new QShortcut( QKeySequence("right"), this );
    connect(act2, SIGNAL(activated()), this, SLOT(move_right()));
    QShortcut* act3 = new QShortcut( QKeySequence("up"), this );
    connect(act3, SIGNAL(activated()), this, SLOT(move_up()));
    QShortcut* act4 = new QShortcut( QKeySequence("down"), this );
    connect(act4, SIGNAL(activated()), this, SLOT(move_down()));
    point_info();

    Dialog* startDialog = new Dialog(this);
    connect(startDialog, &Dialog::accepted, this, &MainWindow::show);
    connect(startDialog, &Dialog::rejected, this, &MainWindow::cancel);
    connect(startDialog, &Dialog::getname, this, &MainWindow::takePlayerName);
    startDialog->show();
}

MainWindow::~MainWindow()
{
    logic.get()->finalizeGameStart();
    delete ui;
    delete timer;
    delete irlTimer;
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
    player_ = new GraphicItem(250, 250, CHARACTER);
    addActor(player_);
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

void MainWindow::createClock()
{
    ui->secondLCD->display(second_);
    ui->minuteLCD->display(minute_);
    ui->secondLCD->setAutoFillBackground(true);
    QPalette p;
    p.setColor(QPalette::Background, QColor(120,0,200));
    ui->secondLCD->setPalette(p);

    ui->minuteLCD->setAutoFillBackground(true);
    p.setColor(QPalette::Background, QColor(120,200,0));
    ui->minuteLCD->setPalette(p);

    ui->minuteLCD->setSegmentStyle(QLCDNumber::Flat);
    ui->secondLCD->setSegmentStyle(QLCDNumber::Flat);

    irlTimer = new QTimer;
    irlTimer->setInterval(1000);
    connect(irlTimer, &QTimer::timeout, this, &MainWindow::addTime);
}

void MainWindow::addTime()
{
    if(!tre.get()->isGameOver()){
        ++second_;
        if(second_ == 60){
            second_ = 0;
            ++minute_;
        }
    }
    if(minute_ == 5){
        tre.get()->endGame();
        timer->stop();
        irlTimer->stop();
        QString points = QString::number(statistics_->getPoints());
        ui->textBrowser->setText(" Game over!\n You got " + points + "\n total points!");
    }
    ui->secondLCD->display(second_);
    ui->minuteLCD->display(minute_);
}

void MainWindow::takePlayerName(QString name)
{
    if(name.isEmpty()){
        playername_ = "Clyde";
        ui->clockLabel->setText(playername_);
    }
    else{
        playername_ = name;
        ui->clockLabel->setText(playername_);
    }
}

void MainWindow::cancel()
{
    // Logic sets up city for proper deletion
    logic.get()->finalizeGameStart();
    close();
}

void MainWindow::on_startbutton_clicked()
{
    logic.get()->finalizeGameStart();
    addGraphics();
    timer->start();
    irlTimer->start();
    emit gameStarted();
    delete startbutton_;
}

void MainWindow::advanceGame()
{
    qDebug() << "advanceGame()";
    logic.get()->increaseTime();
    std::vector<std::shared_ptr<IActor> > near = tre.get()->getNearbyActors(player_->getcharacter().get()->giveLocation());

    for(auto it = near.begin(); it != near.end(); ++it){
        if(dynamic_cast<Nysse*>(it->get()) != nullptr){
            tre->removeActor(*it);
            statistics_->add_points("bus");
        /*}else if(dynamic_cast<????*>(it->get()) != nullptr){
            tre->removeActor(*it);
            statistics_->add_points("plane");*/
        }
    }

    player_->updateGraphic(0,0);
    updateGraphics();
    map->update();
    point_info();
    action_taken_ = false;
}

void MainWindow::move_left()
{
    if(tre.get()->isGameOver()){
        return;
    }
    else if(action_taken_ == false){
        action_taken_ = true;
        player_->getcharacter().get()->movement_commands("left");
    }
}

void MainWindow::move_right()
{
    if(tre.get()->isGameOver()){
        return;
    }
    else if(action_taken_ == false){
        action_taken_ = true;
        player_->getcharacter().get()->movement_commands("right");
    }
}

void MainWindow::move_up()
{
    if(tre.get()->isGameOver()){
        return;
    }
    else if(action_taken_ == false){
        action_taken_ = true;
        player_->getcharacter().get()->movement_commands("up");
    }
}

void MainWindow::move_down()
{
    if(tre.get()->isGameOver()){
        return;
    }
    else if(action_taken_ == false){
        action_taken_ = true;
        player_->getcharacter().get()->movement_commands("down");
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
