#include "airplane.hh"


StudentSide::Airplane::Airplane(int x, int y) :
    removed_(false)
{
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
