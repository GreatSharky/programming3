#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "city.h"
#include "stopgraphic.h"
#include "busgraphic.h"
#include "character.hh"
#include "dialog.h"
#include "offlinereader.hh"
#include "graphics/simpleactoritem.hh"
#include "actors/nysse.hh"
#include "core/logic.hh"

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QDialog>
#include <iostream>
#include <memory>
#include <map>

#include <QKeyEvent>

enum GraphicItems {NOTHING, STOP, BUS, PASSENGER, other};

namespace Ui {
class MainWindow;
}

namespace Aaro {
/**
 * @brief The MainWindow class
 * Window where the game is played
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setTick(int t);

    void addActor(int locX, int locY, GraphicItems type = NOTHING);
    void updateCoords(int nX, int nY);
    void setPicture(QImage &img);

signals:
    void gameStarted();

private slots:
    void on_startbutton_clicked();
    void advanceGame();
    void updateBuses();
    void character_movement(QString command);

private:
    bool addInformation();


    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<QGraphicsPixmapItem*> vehicles_;
    QVector<QGraphicsItem*> stops_;
    QGraphicsItem* last_;
    character *dude_;
    QPushButton *startbutton_;

    std::shared_ptr<CourseSide::Logic> logic;

    std::shared_ptr<City> tre;

    bool dataread_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

}

#endif // MAINWINDOW_H
