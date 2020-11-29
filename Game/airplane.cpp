#include "airplane.hh"


StudentSide::airplane::airplane() :
    removed_(false)
{
    path();
}

StudentSide::airplane::~airplane()
{

}

Location StudentSide::airplane::giveLocation() const
{
    return location_;
}

void StudentSide::airplane::move(Location loc)
{
    location_ = loc;
}

void StudentSide::airplane::remove()
{
    removed_ = true;
}

bool StudentSide::airplane::isRemoved() const
{
    return removed_;
}

void StudentSide::airplane::path()
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
