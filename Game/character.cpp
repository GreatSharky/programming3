#include "character.hh"

StudentSide::Character::Character(int x, int y) :
    removed_(false)
{
    location_.setXY(x, y);
}

StudentSide::Character::~Character()
{

}

Location StudentSide::Character::giveLocation() const
{
    return location_;
}

void StudentSide::Character::move(Location loc)
{
    location_ = loc;

}

void StudentSide::Character::remove()
{
    removed_ = true;
}

bool StudentSide::Character::isRemoved() const
{
    return removed_;
}

void StudentSide::Character::movement_commands(QString command)
{
    if(command == "left"){
        location_.setXY(location_.giveX() -10, location_.giveY());

    }else if(command == "right"){
        location_.setXY(location_.giveX() +10 , location_.giveY());

    }else if(command == "up"){
        location_.setXY(location_.giveX(), location_.giveY() + 10);

    }else if(command == "down"){
        location_.setXY(location_.giveX(), location_.giveY() - 10);
    }
}
