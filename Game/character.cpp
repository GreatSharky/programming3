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
        qDebug() << "vasen";
        // Paha sanoo mitää täst
        location_.setXY(location_.giveX() -10, location_.giveY());

    }else if(command == "right"){
        qDebug() << "oikee";
        location_.setXY(location_.giveX() +10 , location_.giveY());

    }else if(command == "up"){
        qDebug() << "ylös";
        location_.setXY(location_.giveX(), location_.giveY() + 10);

    }else if(command == "down"){
        qDebug() << "alas";
        location_.setXY(location_.giveX(), location_.giveY() - 10);
    }
}
