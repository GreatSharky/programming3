#ifndef CITY_H
#define CITY_H

#include "graphicitem.h"
#include "interfaces/icity.hh"
#include "actors/stop.hh"
#include "actors/nysse.hh"


#include <QString>
#include <QTime>
#include <QDebug>
#include <map>


using namespace Interface;
using namespace CourseSide;

namespace U {
class MainWindow;
}

namespace Aaro{
// Forward decleration
class MainWindow;


/**
 *Defines city
 */
class City : public ICity
{
public:
    /**
     * @brief City
     */
    City();
    ~City();
    /**
     * @brief defined in ICity
     */
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    void startGame() override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<IStop> stop) override;
    void actorMoved(std::shared_ptr<IActor> actor) override;
    void addActor(std::shared_ptr<IActor> newactor) override;
    void removeActor(std::shared_ptr<IActor> actor) override;
    void actorRemoved(std::shared_ptr<IActor> actor) override;
    std::vector<std::shared_ptr<IActor> > getNearbyActors(Location loc) const override;
    bool isGameOver() const override;
    bool findActor(std::shared_ptr<IActor> actor) const override;

    /**
     * @brief getBackground
     * @throw maps = nullptr
     * @return
     */
    QImage *getBackground();

    /**
     * @brief getStops
     * @return vector to city stops
     */
    std::vector<std::shared_ptr<IStop> > getStops();

    /**
     * @brief setGameWindow gives city the mainwindow
     * @param window
     */
    void setGameWindow(MainWindow* window);

    // test from olden days
    int test();

private:
    QImage* map_;
    QImage* bigmap_;
    std::vector<std::shared_ptr<IStop> > stops_;
    std::map<std::shared_ptr<Interface::IActor>, std::shared_ptr<GraphicItem> > vehicles_;
    std::vector<std::shared_ptr<IActor> > passengers_;

    QTime* clock_;

    Aaro::MainWindow* game;


    bool gameLive_;

};
}
#endif // CITY_H
