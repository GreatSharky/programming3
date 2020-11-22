#include "busgraphic.h"


Aaro::BusGraphic::BusGraphic(int x, int y, int type):
    QGraphicsPixmapItem()
{
    filename = ":/bus-icon.png";
    QPixmap bigGraphic(filename);
    picture = bigGraphic.scaled(50,50);
    dir_ = 1;
    setPixmap(picture);
    type_=type;
    setX(x);
    setY(y);
}

void Aaro::BusGraphic::updateGraphic(int newX, int newY)
{
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

int Aaro::BusGraphic::getType()
{
    return type_;
}
