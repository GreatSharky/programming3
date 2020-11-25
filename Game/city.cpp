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

void Aaro::City::startGame()
{
    gameLive_ = true;
}

void Aaro::City::setClock(QTime clock)
{
    if(clock.isValid()){
        clock_->setHMS(clock.hour(),clock.minute(),clock.second());
    }
}

void Aaro::City::addStop(std::shared_ptr<IStop> stop)
{
    stops_.push_back(stop);
}

void Aaro::City::actorMoved(std::shared_ptr<IActor> actor)
{
    if(std::dynamic_pointer_cast<Interface::IVehicle>(actor)){
        for(auto it = vehicles_.begin(); it != vehicles_.end(); ++it){
            if(it->first == actor){
                int x = it->first.get()->giveLocation().giveX();
                int y = 500 - it->first.get()->giveLocation().giveY();
                it->second.get()->updateGraphic(x,y);
            }
        }
    }
}

void Aaro::City::addActor(std::shared_ptr<IActor> newactor)
{
    if(std::dynamic_pointer_cast<CourseSide::Nysse>(newactor)){
        qDebug() << "Nysse added";
        std::shared_ptr<GraphicItem> pic = std::make_shared<GraphicItem>(GraphicItem(newactor->giveLocation().giveX(),
                                            500-newactor->giveLocation().giveY(),BUS));
        vehicles_.insert({newactor, pic});
        // Lisää mainwondwiin vs
    }
}

void Aaro::City::removeActor(std::shared_ptr<IActor> actor)
{

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


void Aaro::City::setGameWindow(MainWindow *window)
{
    game = window;
}

int Aaro::City::test()
{
    return 1;
}
