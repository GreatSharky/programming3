#include "busgraphic.h"


Aaro::BusGraphic::BusGraphic(int x, int y, int type):
    QGraphicsPixmapItem()
{
    filename = ":/bus-icon.png";
    QPixmap bigGraphic(filename);
    picture = bigGraphic.scaled(50,50);
    setPixmap(picture);
    type_=type;
    setX(x);
    setY(y);
}

void Aaro::BusGraphic::updateGraphic(int newX, int newY)
{
    // Jos suunta on eri kuin ennen flippaa picture
    // Miten?
    int tempdir = dir_;

}

int Aaro::BusGraphic::giveType()
{
    return type_;
}
