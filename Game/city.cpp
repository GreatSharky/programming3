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
}

void Aaro::City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    map_ = &basicbackground;
    bigmap_ = &bigbackground;
}

void Aaro::City::setClock(QTime clock)
{
    clock_->setHMS(clock.hour(),clock.minute(),clock.second());
}

void Aaro::City::addStop(std::shared_ptr<IStop> stop)
{
    // Test that location is set right
    if(stop.get()->getLocation().giveNorthernCoord() != 6700000 && stop.get()->getLocation().giveEasternCoord() != 3500000){
        GraphicItem* stpgraphic = new GraphicItem(stop.get()->getLocation().giveX(), 500-stop.get()->getLocation().giveY(), STOP);
        stops_.insert({stop, stpgraphic});
    }
    else{
        throw InitError("addStop, stop location not valid");
    }
}

void Aaro::City::startGame()
{
    gameLive_ = true;
}

void Aaro::City::addActor(std::shared_ptr<IActor> newactor)
{
    if(!findActor(newactor)){
        if(dynamic_cast<CourseSide::Nysse*>(newactor.get()) != nullptr){
            GraphicItem* pic = new GraphicItem(newactor->giveLocation().giveX(), 500-newactor->giveLocation().giveY(),BUS);
            vehicles_.insert({newactor, pic});
        }
        else if(dynamic_cast<airplane*>(newactor.get()) != nullptr){
            GraphicItem* pic = new GraphicItem(newactor->giveLocation().giveX(), 500-newactor->giveLocation().giveY(), PLANE);
            vehicles_.insert({newactor,pic});
        }
    }
    else{
        throw GameError("addActor, actor already in city");
    }
}

void Aaro::City::removeActor(std::shared_ptr<IActor> actor)
{
    if(findActor(actor)){
        for(auto it =  vehicles_.begin(); it != vehicles_.end(); ++it){
            if(actor == it->first){
                removedItems_.push_back(it->second);
                if(actor.get()->isRemoved()){
                    actor.get()->remove();
                }/*
            if(it->second == nullptr){
                delete it->second;
            }*/
                vehicles_.erase(it);
            }
        }
    }
    else{
        throw GameError("removeActor, actor not found in the city");
    }
}

void Aaro::City::actorRemoved(std::shared_ptr<IActor> actor)
{
    qDebug() << "someone called actorRemoved" << actor.get();
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
    if(std::dynamic_pointer_cast<Interface::IVehicle>(actor)){
        for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
            if(it->first == actor){
                int x = it->first.get()->giveLocation().giveX();
                int y = 500 - it->first.get()->giveLocation().giveY();
                it->second->updateGraphic(x,y);
            }
        }
    }
}

std::vector<std::shared_ptr<IActor> > Aaro::City::getNearbyActors(Location loc) const
{
    std::vector<std::shared_ptr<IActor> > near;
    int distance = 10;
    for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
        if(loc.isClose(it->first.get()->giveLocation(), distance)){
            near.push_back(it->first);
        }
    }
    return near;
}

bool Aaro::City::isGameOver() const
{
    return !gameLive_;
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
        throw GameError("No valid map.");
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

std::vector<Aaro::GraphicItem *> Aaro::City::getRemoved()
{
    return removedItems_;
}

void Aaro::City::clearRemoved()
{
    removedItems_.clear();
}

void Aaro::City::endGame()
{
    gameLive_ = false;
}

int Aaro::City::test()
{
    return 1;
}
