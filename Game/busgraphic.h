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
    int giveType();

private:
    int type_;
    QString filename;
};
}

#endif // BUSGRAPHIC_H
