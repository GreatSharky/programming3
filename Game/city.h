#ifndef CITY_H
#define CITY_H

#include "interfaces/icity.hh"
#include "actors/stop.hh"


#include <QString>
#include <QTime>
#include <QDebug>


using namespace Interface;
using namespace CourseSide;


/**
 *Defines city
 */
namespace Aaro{

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

    // test from olden days
    int test();

private:
    QImage* map_;
    QImage* bigmap_;
    std::vector<std::shared_ptr<IStop> > stops_;

};
}
#endif // CITY_H
