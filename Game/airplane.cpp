#include "airplane.hh"


StudentSide::Airplane::Airplane() :
    removed_(false)
{
    int x = (rand() % 400) + 100;
    int y = (rand() % 400) + 100;
    location_.setXY(x, y);
}

StudentSide::Airplane::~Airplane()
{

}

Location StudentSide::Airplane::giveLocation() const
{
    return location_;
}

void StudentSide::Airplane::move(Location loc)
{
    location_ = loc;
}

void StudentSide::Airplane::remove()
{
    removed_ = true;
}

bool StudentSide::Airplane::isRemoved() const
{
    return removed_;
}
