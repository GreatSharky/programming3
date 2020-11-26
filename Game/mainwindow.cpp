#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Aaro;

Aaro::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    action_taken_(false)
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
    installEventFilter(this);
    QString picfile = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    QImage pic(picfile);
    setPicture(pic);




    dude_ = new character(250, 250);
    //addActor(dude_->giveLocation().giveX(), dude_->giveLocation().giveY(), NOTHING);
    // Täl voi ny piirtää grafiikat. tuli musta pallo näytöl
    show();

}

MainWindow::~MainWindow()
{
    // Remove graghics
    delete ui;
}

void MainWindow::setTick(int t)
{
    timer->setInterval(t);
}

void MainWindow::addActor(BusGraphic *actorPic)
{
    map->addItem(actorPic);
    actors_.push_back(actorPic);
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

bool MainWindow::addInformation()
{

}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress && action_taken_ == false){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        action_taken_ = true;
        switch (keyEvent->key()){
            case Qt::Key_Up:
                dude_->movement_commands("up");
                break;
            case Qt::Key_Down:
                dude_->movement_commands("down");
                break;
            case Qt::Key_Left:
                dude_->movement_commands("left");
                break;
            case Qt::Key_Right:
                dude_->movement_commands("right");
                break;
        }
        return QObject::eventFilter(object, event);
    }
    return true;
}

void MainWindow::on_startbutton_clicked()
{
    timer->start();
    emit gameStarted();
    delete startbutton_;
}
