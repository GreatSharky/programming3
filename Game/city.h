#ifndef CITY_H
#define CITY_H

#include "graphicitem.h"
#include "interfaces/icity.hh"
#include "actors/stop.hh"
#include "actors/nysse.hh"
#include "errors/initerror.hh"
#include "errors/gameerror.hh"


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
     * @return map of city stops
     */
    std::map<std::shared_ptr<IStop>, GraphicItem *> getStops();

    /**
     * @brief getVehicles
     * @return map of city vehicles
     */
    std::map<std::shared_ptr<Interface::IActor>, GraphicItem *> getVehicles();

    /**
     * @brief getRemoved
     * @return removed graphic items
     */
    std::vector<GraphicItem *> getRemoved();

    /**
     * @brief clearRemoved clears removed items
     */
    void clearRemoved();

    // test from olden days
    int test();

private:
    QImage* map_;
    QImage* bigmap_;
    std::map<std::shared_ptr<IStop>, GraphicItem* > stops_;
    std::map<std::shared_ptr<Interface::IActor>, GraphicItem* > vehicles_;
    std::vector<GraphicItem*> removedItems_;
    std::vector<std::shared_ptr<IActor> > passengers_;

    QTime* clock_;



    bool gameLive_;

};
}
#endif // CITY_H
