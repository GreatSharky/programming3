#include "graphicitem.h"

Aaro::GraphicItem::GraphicItem(int x, int y, GraphicsItem type):
    QGraphicsPixmapItem(nullptr), x_(x), y_(y), type_(type), dir_(0)
{
    selectIcon();
    setPixmap(picture);
    setX(x_);
    setY(y_);
}

Aaro::GraphicItem::~GraphicItem()
{

}

void Aaro::GraphicItem::updateGraphic(int newX, int newY)
{
    if(type_ == STOP){
        return;
    }
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
    x_ = newX;
    y_ = newY;
    setX(x_);
    setY(y_);
}

GraphicsItem Aaro::GraphicItem::getType()
{
    return type_;
}

void Aaro::GraphicItem::selectIcon()
{
    if(type_ == STOP){
        QPixmap bigGraphic(":/bus-stop-icon.png");
        picture = bigGraphic.scaled(40,40);
    }
    else if(type_ == BUS){
        QPixmap bigGraphic(":/bus-icon.png");
        picture = bigGraphic.scaled(50,50);
        setOffset(QPointF(-30,-30));
    }
    else if(type_ == CHARACTER){
        QPixmap bigGraphic(":/pacmanghost2-icon.png");
        picture = bigGraphic.scaled(30, 30);
        setOffset(QPointF(-15,-15));
    }
    else if(type_ == PLANE){
        QPixmap bigGraphic(":/plane-icon.png");
        picture = bigGraphic.scaled(40,40);
    }
    else {
        qDebug() << "No icon for:" << type_;
    }
}
