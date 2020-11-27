#include "statistics.hh"

Aaro::statistics::statistics() :
    points_(0),
    planes_(0),
    buses_(0)
{

}

Aaro::statistics::~statistics()
{

}

void Aaro::statistics::morePassengers(int num)
{
    qDebug() << num << " new passangers added.";

}

void Aaro::statistics::nysseRemoved()
{
    qDebug() << "Nysse is removed from the game.";
}

void Aaro::statistics::newNysse()
{
    qDebug() << "New nysse has been added to the game.";
}

void Aaro::statistics::nysseLeft()
{
    qDebug() << "Nysse has left the game.";
}

void Aaro::statistics::add_points(QString vehicle)
{
    if(vehicle == "bus"){
        points_ += 10;
        ++buses_;

    }else if(vehicle == "plane"){
        points_ += 25;
        ++planes_;

    }else{
        throw GameError("Not a valid vehicle.");
    }
}

int Aaro::statistics::getPoints()
{
    return points_;
}

int Aaro::statistics::getPlanes()
{
    return planes_;
}

int Aaro::statistics::getBuses()
{
    return buses_;
}

