#ifndef CITY_H
#define CITY_H

#include "mainwindow.h"
#include "graphicitem.h"
#include "busgraphic.h"
#include "interfaces/icity.hh"
#include "actors/stop.hh"
#include "actors/nysse.hh"
#include "core/logic.hh"


#include <QString>
#include <QTime>
#include <QDebug>
#include <map>


using namespace Interface;
using namespace CourseSide;


namespace Aaro{
// Forward decleration


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
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<IActor> newactor) override;
    void removeActor(std::shared_ptr<IActor> actor) override;
    void actorRemoved(std::shared_ptr<IActor> actor) override;
    bool findActor(std::shared_ptr<IActor> actor) const override;
    void actorMoved(std::shared_ptr<IActor> actor) override;
    std::vector<std::shared_ptr<IActor> > getNearbyActors(Location loc) const override;
    bool isGameOver() const override;

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

    // test from olden days
    int test();

private:
    std::shared_ptr<CourseSide::Logic> logic;

    QImage* map_;
    QImage* bigmap_;
    std::vector<std::shared_ptr<IStop> > stops_;
    std::map<std::shared_ptr<Interface::IActor>, std::shared_ptr<BusGraphic> > vehicles_;
    std::vector<std::shared_ptr<IActor> > passengers_;

    QTime* clock_;

    MainWindow* game;


    bool gameLive_;

};
}
#endif // CITY_H
