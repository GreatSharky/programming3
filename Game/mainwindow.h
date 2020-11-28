#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "character.hh"
#include "statistics.hh"
#include "graphicitem.h"
#include "city.h"
#include "dialog.h"
#include "graphics/simpleactoritem.hh"
#include "core/logic.hh"

#include <QObject>
#include <QWidget>
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
#include <QKeySequence>
#include <QShortcut>

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
    void addGraphics();
    void updateGraphics();
    void point_info();

signals:
    void gameStarted();

private slots:
    void takePlayerName(QString name);
    void cancel();
    void on_startbutton_clicked();
    void advanceGame();
    void move_left();
    void move_right();
    void move_up();
    void move_down();


private:
    bool inMap(GraphicItem* item);

    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<GraphicItem*> actors_;
    QGraphicsItem* last_;
    GraphicItem *dude_;
    QPushButton *startbutton_;
    bool action_taken_;
    statistics *statistics_;

    std::shared_ptr<CourseSide::Logic> logic;

    std::shared_ptr<City> tre;

    QString playername_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

}

#endif // MAINWINDOW_H
