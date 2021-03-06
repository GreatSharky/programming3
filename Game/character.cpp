#include "character.hh"

Aaro::character::character(int x, int y) :
    removed_(false)
{
    location_.setXY(x, y);
}

Aaro::character::~character()
{

}

Location Aaro::character::giveLocation() const
{
    return location_;
}

void Aaro::character::move(Location loc)
{
    location_ = loc;
}

void Aaro::character::remove()
{
    removed_ = true;
}

bool Aaro::character::isRemoved() const
{
    return removed_;
}

void Aaro::character::movement_commands(QString command)
{
    if(command == "left"){
        qDebug() << "liikkuu";
        // Paha sanoo mitää täst
        Location newloc = Location(location_.giveX() - 10, location_.giveY());
        move(newloc);

    }else if(command == "right"){
        Location newloc = Location(location_.giveX() + 10, location_.giveY());
        move(newloc);

    }else if(command == "up"){
        Location newloc = Location(location_.giveX(), location_.giveY() - 10);
        move(newloc);

    }else if(command == "down"){
        Location newloc = Location(location_.giveX(), location_.giveY() + 10);
        move(newloc);
    }
}
