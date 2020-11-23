#include "city.h"


Aaro::City::City():
    clock_(new QTime)
{
    qDebug() << "City built";
    gameLive_ = false;
}

Aaro::City::~City()
{

}

void Aaro::City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    map_ = &basicbackground;
    bigmap_ = &bigbackground;
}

void Aaro::City::startGame()
{
    gameLive_ = true;
}

void Aaro::City::setClock(QTime clock)
{
    clock_->setHMS(clock.hour(),clock.minute(),clock.second());
}

void Aaro::City::addStop(std::shared_ptr<IStop> stop)
{
    stops_.push_back(stop);
}

void Aaro::City::actorMoved(std::shared_ptr<IActor> actor)
{

}

void Aaro::City::addActor(std::shared_ptr<IActor> newactor)
{
    if(dynamic_cast<CourseSide::Nysse*>(newactor.get()) != nullptr){
        vehicles_.push_back(newactor);
    }
    else {
        passengers_.push_back(newactor);
    }

}

void Aaro::City::removeActor(std::shared_ptr<IActor> actor)
{
    for(uint it = 0; it < vehicles_.size(); ++it){
        if(actor.get() == vehicles_[it].get()){
            vehicles_.erase(vehicles_.begin() + it-1);
        }
    }
}

void Aaro::City::actorRemoved(std::shared_ptr<IActor> actor)
{

}

std::vector<std::shared_ptr<IActor> > Aaro::City::getNearbyActors(Location loc) const
{

}

bool Aaro::City::isGameOver() const
{
    return false;
}

bool Aaro::City::findActor(std::shared_ptr<IActor> actor) const
{
    for(uint it = 0; it < vehicles_.size(); ++it){
        if(vehicles_[it].get() == actor.get()){
            return true;
        }
    }
    for(uint it = 0; it < passengers_.size(); ++it){
        if( passengers_[it].get() == actor.get()){
            return true;
        }
    }
    return false;
}

QImage* Aaro::City::getBackground()
{
    if(map_ != nullptr){
        return  map_;
    }
    else if(bigmap_ != nullptr) {
        return bigmap_;
    }
    else{
        // throw error
    }
}

std::vector<std::shared_ptr<IStop> > Aaro::City::getStops()
{
    return stops_;
}

std::vector<std::shared_ptr<IActor> > Aaro::City::getBuses()
{
    return vehicles_;
}

int Aaro::City::test()
{
    return 1;
}
