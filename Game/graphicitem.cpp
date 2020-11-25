#include "graphicitem.h"

Aaro::GraphicItem::GraphicItem(int x, int y, GraphicsItem type):
    QGraphicsPixmapItem(nullptr), x_(x), y_(y), type_(type)
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
        if(x_ - newX < 0){
            dir_ = -1;
            picture = picture.transformed(QTransform().scale(-1,1));
            setPixmap(picture);
        }
    }
    else if( dir_ > 0){
        if(x_ - newX > 0){
            dir_ = 1;
            picture = picture.transformed(QTransform().scale(-1,1));
            setPixmap(picture);
        }
    }
    else{
        qDebug() << "Not possible";
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
        picture = bigGraphic.scaled(40,40);
    }
    else {
        qDebug() << "No icon for:" << type_;
    }
}
