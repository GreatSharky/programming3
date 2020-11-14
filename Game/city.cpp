#include "city.h"


Aaro::City::City()
{
    qDebug() << "City built";
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

}

void Aaro::City::setClock(QTime clock)
{

}

void Aaro::City::addStop(std::shared_ptr<IStop> stop)
{
    stops_.push_back(stop);
    qDebug() << stops_.size();
}

void Aaro::City::actorMoved(std::shared_ptr<IActor> actor)
{

}

void Aaro::City::addActor(std::shared_ptr<IActor> newactor)
{

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

}

bool Aaro::City::findActor(std::shared_ptr<IActor> actor) const
{

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

int Aaro::City::test()
{
    return 1;
}
