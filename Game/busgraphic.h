#ifndef BUSGRAPHIC_H
#define BUSGRAPHIC_H

#include "actors/nysse.hh"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <memory>

namespace Aaro {



class BusGraphic : public QGraphicsPixmapItem
{
public:
    BusGraphic(int x, int y, int type);
    void updateGraphic(int newX, int newY);
    int getType();

private:
    int type_;
    int x_;
    int y_;
    int dir_;
    QPixmap picture;
    QString filename;
};
}

#endif // BUSGRAPHIC_H
