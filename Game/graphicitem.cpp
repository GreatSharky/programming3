#include "graphicitem.h"

StudentSide::GraphicItem::GraphicItem(int x, int y, GraphicsItem type):
    QGraphicsPixmapItem(nullptr), x_(x), y_(y), type_(type), dir_(0)
{
    selectIcon();
    setPixmap(picture);
    setX(x_);
    setY(y_);
}

StudentSide::GraphicItem::~GraphicItem()
{

}

void StudentSide::GraphicItem::updateGraphic(int newX, int newY)
{
    if(type_ == STOP){
        return;
    }
    else if(type_ == BUS){
        if(dir_ < 0){
            if(x_ - newX > 0){
                dir_ = 1;
                picture = picture.transformed(QTransform().scale(-1,1));
                setPixmap(picture);
            }
        }
        else if( dir_ >= 0){
            if(x_ - newX < 0){
                dir_ = -1;
                picture = picture.transformed(QTransform().scale(-1,1));
                setPixmap(picture);
            }
        }

    }
    else if(type_ == CHARACTER){
        newX = character_.get()->giveLocation().giveX();
        newY = 500 - character_.get()->giveLocation().giveY();
    }
    else if(type_ == PLANE){
        newX = plane_.get()->giveLocation().giveX();
        newY = plane_.get()->giveLocation().giveY();
    }
    x_ = newX;
    y_ = newY;
    setX(x_);
    setY(y_);

}

GraphicsItem StudentSide::GraphicItem::getType()
{
    return type_;
}

std::shared_ptr<StudentSide::Character> StudentSide::GraphicItem::getcharacter()
{
    if(type_ == CHARACTER){
        return character_;
    }
    else{
        return nullptr;
    }
}

std::shared_ptr<StudentSide::Airplane> StudentSide::GraphicItem::getAirplane()
{
    if(type_ == PLANE){
        return plane_;
    }
    else{
        return nullptr;
    }
}

void StudentSide::GraphicItem::selectIcon()
{
    if(type_ == STOP){
        QPixmap bigGraphic(":/bus-stop-icon.png");
        picture = bigGraphic.scaled(35,35);
        setOffset(QPointF(-20,-32));
    }
    else if(type_ == BUS){
        QPixmap bigGraphic(":/bus-icon.png");
        picture = bigGraphic.scaled(50,50);
        setOffset(QPointF(-30,-30));
    }
    else if(type_ == CHARACTER){
        makeCharacter();
        QPixmap bigGraphic(":/pacmanghost2-icon.png");
        picture = bigGraphic.scaled(30, 30);
        setOffset(QPointF(-15,-15));

    }
    else if(type_ == PLANE){
        makePlane();
        QPixmap bigGraphic(":/plane-icon.png");
        picture = bigGraphic.scaled(40,40);
        setOffset(-20,-20);
    }
    else {
        qDebug() << "No icon for:" << type_;
    }
}

void StudentSide::GraphicItem::makeCharacter()
{
    character_ = std::make_shared<Character>(x_,y_);
}

void StudentSide::GraphicItem::makePlane()
{
    x_ = (rand() % 400) + 100;
    y_ = (rand() % 400) + 100;
    plane_ = std::make_shared<Airplane>(x_, y_);
}
