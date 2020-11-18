#include "busgraphic.h"


Aaro::BusGraphic::BusGraphic(int x, int y, int type):
    QGraphicsPixmapItem()
{
    filename = ":/bus-icon.png";
    QPixmap bigGraphic(filename);
    QPixmap realGraphic = bigGraphic.scaled(50,50);
    //QPixmap flipped = realGraphic.transformed(QTransform().scale(-1,1));
    setPixmap(realGraphic);
    type_=type;
    setX(x);
    setY(y);
}

int Aaro::BusGraphic::giveType()
{
    return type_;
}
