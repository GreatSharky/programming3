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
    this->setFixedSize(width_ + 400, height_ + 200); // Lisäilin vähä

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
    //installEventFilter(this);
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
    character cha = character(250,250);
    dude_ = std::make_shared<character>(cha);
    map->addItem(dude_.get()->getGraphic());

    dude_.get()->getGraphic()->setFlag(QGraphicsPixmapItem::ItemIsFocusable, true);
    dude_.get()->getGraphic()->setFocus();
    // Täl voi ny piirtää grafiikat. tuli musta pallo näytöl
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

void MainWindow::keyPressedEvent(QKeyEvent *event)
{
   if(action_taken_ == false){
        action_taken_ = true;
        if(event->key() == Qt::Key_Left){
            dude_->movement_commands("left");

        }else if(event->key() == Qt::Key_Down){
            dude_->movement_commands("down");

        }else if(event->key() == Qt::Key_Up){
            dude_->movement_commands("up");

        }else if(event->key() == Qt::Key_Right){
            dude_->movement_commands("right");
        }
    }
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
    try{
        qDebug() << "advanceGame()";
        logic.get()->increaseTime();
        dude_->move(dude_->giveLocation());
        updateGraphics();
        map->update();
        action_taken_ = false;
    }
    catch(InitError const &error){
        qDebug() << error.what() << error.giveMessage();
    }
    catch(GameError const &error){
        qDebug() << error.what() << error.giveMessage();
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
