#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "city.h"
#include "graphicitem.h"
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

    void addActor(GraphicItem* actorPic);
    void updateCoords(int nX, int nY);
    void setPicture(QImage &img);

signals:
    void gameStarted();

private slots:
    void on_startbutton_clicked();
    void advanceGame();
    void updateBuses();


private:
    bool addInformation();
    bool eventFilter(QObject *object, QEvent *event);

    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<GraphicItem*> actors_;
    QGraphicsItem* last_;
    character *dude_;
    QPushButton *startbutton_;
    bool action_taken_;

    std::shared_ptr<CourseSide::Logic> logic;

    std::shared_ptr<City> tre;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

}

#endif // MAINWINDOW_H
