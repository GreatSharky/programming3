#include "stopgraphic.h"


Aaro::StopGraphic::StopGraphic(int x, int y, int type):
    QGraphicsPixmapItem()
{
    filename = "/home/haikone3/ohjelmointi3/aaro-ja-eero/Game/bus-stop-icon.png";
    QPixmap bigGraphic(filename);
    QPixmap realGraphic = bigGraphic.scaled(40,40);
    setPixmap(realGraphic);
    type_ = type;
    setX(x);
    setY(y);
    qDebug() << this->x() <<"/" << this->y();
}

int Aaro::StopGraphic::giveType()
{
    return type_;
}
