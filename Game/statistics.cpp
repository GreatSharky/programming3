#include "statistics.hh"

StudentSide::statistics::statistics() :
    points_(0),
    planes_(0),
    buses_(0)
{

}

StudentSide::statistics::~statistics()
{

}

void StudentSide::statistics::morePassengers(int num)
{
    qDebug() << num << " new passangers added.";

}

void StudentSide::statistics::nysseRemoved()
{
    qDebug() << "Nysse is removed from the game.";
}

void StudentSide::statistics::newNysse()
{
    qDebug() << "New nysse has been added to the game.";
}

void StudentSide::statistics::nysseLeft()
{
    qDebug() << "Nysse has left the game.";
}

void StudentSide::statistics::add_points(QString vehicle)
{
    if(vehicle == "bus"){
        points_ += 10;
        ++buses_;

    }else if(vehicle == "plane"){
        points_ += 25;
        ++planes_;
    }
}

int StudentSide::statistics::getPoints()
{
    return points_;
}

int StudentSide::statistics::getPlanes()
{
    return planes_;
}

int StudentSide::statistics::getBuses()
{
    return buses_;
}

