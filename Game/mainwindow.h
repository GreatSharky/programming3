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

namespace StudentSide {


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
    /**
     * @brief Sets the game tick
     * @param The amount for a tick
     */
    void setTick(int t);
    /**
     * @brief Adds the actors to the game
     * @param The actor thats added to the game
     */
    void addActor(GraphicItem* actorPic);
    /**
     * @brief Updates the coordinates
     * @param The new x-coordinate
     * @param The new y-coordinate
     */
    void updateCoords(int nX, int nY);
    /**
     * @brief Adds graphics to the actors
     */
    void addGraphics();
    /**
     * @brief Updates the graphics
     */
    void updateGraphics();
    /**
     * @brief Adds the necessary info to the window
     */
    void point_info();
    /**
     * @brief Creates the game clock
     */
    void createClock();

signals:
    void gameStarted();

private slots:
    /**
     * @brief Adds time to the clock
     */
    void addTime();
    /**
     * @brief Gets the name of the player
     * @param Name of the player
     */
    void takePlayerName(QString name);
    /**
     * @brief Cancels the game
     */
    void cancel();
    /**
     * @brief Starts the game when start button is clicked
     */
    void on_startbutton_clicked();
    /**
     * @brief Advances the game every tick
     */
    void advanceGame();
    /**
     * @brief Moves the character to the left
     */
    void move_left();
    /**
     * @brief Moves the character to the right
     */
    void move_right();
    /**
     * @brief Moves the character to the up
     */
    void move_up();
    /**
     * @brief Moves the character to the down
     */
    void move_down();


private:
    /**
     * @brief Checks if the actor is in the map
     * @param The graphicof the item
     * @return Boolean value of whether the item is found
     */
    bool inMap(GraphicItem* item);

    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;

    // Same speed as real timer
    QTimer *irlTimer;
    QVector<GraphicItem*> actors_;
    QGraphicsItem* last_;
    GraphicItem *player_;
    GraphicItem *plane_;
    QPushButton *startbutton_;
    bool action_taken_;
    bool plane_created_;
    statistics *statistics_;

    std::shared_ptr<CourseSide::Logic> logic;

    std::shared_ptr<City> tre;

    QString playername_;

    int minute_ = 0;
    int second_ = 0;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 33; //ms
};

}

#endif // MAINWINDOW_H
