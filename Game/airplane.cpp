#include "airplane.hh"


Aaro::airplane::airplane() :
    removed_(false)
{
    path();
}

Aaro::airplane::~airplane()
{

}

Location Aaro::airplane::giveLocation() const
{
    return location_;
}

void Aaro::airplane::move(Location loc)
{
    location_ = loc;
}

void Aaro::airplane::remove()
{
    removed_ = true;
}

bool Aaro::airplane::isRemoved() const
{
    return removed_;
}

void Aaro::airplane::path()
{
    int side = rand() % 5;
    int point = rand() % (400 - 100 + 1) + 100;

    if(side == 1){
        location_.setXY(point, 0);
        direction_ = "up";

    }else if(side == 2){
        location_.setXY(500, point);
        direction_ = "left";

    }else if(side == 3){
        location_.setXY(point, 500);
        direction_ = "down";

    }else{
        location_.setXY(0, point);
        direction_ = "right";
    }
}
