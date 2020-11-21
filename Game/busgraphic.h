#ifndef BUSGRAPHIC_H
#define BUSGRAPHIC_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

namespace Aaro {



class BusGraphic : public QGraphicsPixmapItem
{
public:
    BusGraphic(int x, int y, int type);
    void updateGraphic(int newX, int newY);
    int giveType();

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
