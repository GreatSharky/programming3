#ifndef CITY_H
#define CITY_H

#include "interfaces/icity.hh"


#include <QString>
#include <QTime>

using namespace Interface;


/**
 *Defines city
 */
namespace Aaro{

class City : public ICity
{
public:
    City();
    ~City();
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
    QImage *getBackground();
    int test();

private:
    QImage* map_;
    QImage* bigmap_ = nullptr;

};
}
#endif // CITY_H
