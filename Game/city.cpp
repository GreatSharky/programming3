#include "city.h"


Aaro::City::City():
    clock_(new QTime)
{
    qDebug() << "City built";
    gameLive_ = false;
}

Aaro::City::~City()
{
    delete bigmap_;
    delete map_;
    delete clock_;
    for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
        if(it->second != nullptr){
            delete it->second;
        }
    }
    for(auto it = stops_.begin(); it != stops_.end(); ++it){
        if(it->second != nullptr){
            delete it->second;
        }
    }
}

void Aaro::City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    map_ = &basicbackground;
    bigmap_ = &bigbackground;
}

void Aaro::City::setClock(QTime clock)
{
    if(clock.isValid()){
        clock_->setHMS(clock.hour(),clock.minute(),clock.second());
    }
}

void Aaro::City::addStop(std::shared_ptr<IStop> stop)
{
    GraphicItem* pic = new GraphicItem(stop.get()->getLocation().giveX(), 500- stop.get()->getLocation().giveY(), STOP);
    stops_.insert({stop, pic});
}

void Aaro::City::startGame()
{
    gameLive_ = true;
}

void Aaro::City::addActor(std::shared_ptr<IActor> newactor)
{
    if(std::dynamic_pointer_cast<CourseSide::Nysse>(newactor)){
        GraphicItem* pic = new GraphicItem(newactor->giveLocation().giveX(), 500-newactor->giveLocation().giveY(),BUS);
        vehicles_.insert({newactor, pic});
    }
}

void Aaro::City::removeActor(std::shared_ptr<IActor> actor)
{

}

void Aaro::City::actorRemoved(std::shared_ptr<IActor> actor)
{

}

bool Aaro::City::findActor(std::shared_ptr<IActor> actor) const
{
    if(dynamic_cast<Nysse*>(actor.get()) != nullptr){
        for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
            if(it->first == actor){
                return true;
            }
        }
    }
    else if(dynamic_cast<IStop*>(actor.get()) != nullptr){
        IStop* stp = dynamic_cast<IStop*>(actor.get());
        for(auto it = stops_.begin(); it != stops_.end(); ++it){
            if(stp == it->first.get()){
                return true;
            }
        }
    }
    return false;
}

void Aaro::City::actorMoved(std::shared_ptr<IActor> actor)
{
    if(dynamic_cast<IVehicle*>(actor.get())!= nullptr){
        for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
            if(it->first == actor){
                int x = it->first.get()->giveLocation().giveX();
                int y = 500 - it->first.get()->giveLocation().giveY();
                it->second->updateGraphic(x,y);
                break;
            }
        }
    }
}

std::vector<std::shared_ptr<IActor> > Aaro::City::getNearbyActors(Location loc) const
{

}

bool Aaro::City::isGameOver() const
{
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

std::map<std::shared_ptr<IStop>, Aaro::GraphicItem *> Aaro::City::getStops()
{
    return stops_;
}

std::map<std::shared_ptr<IActor>, Aaro::GraphicItem *> Aaro::City::getVehicles()
{
    return vehicles_;
}

int Aaro::City::test()
{
    return 1;
}
