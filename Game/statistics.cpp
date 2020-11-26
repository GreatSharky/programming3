#include "statistics.hh"

Aaro::statistics::statistics() :
    points_(0)
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

void Aaro::statistics::add_points(int new_points)
{
    points_ += new_points;
}
