#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>


enum GraphicsItem {NOTHING, STOP, BUS, PLANE ,OTHER};

namespace Aaro {


class GraphicItem: public QGraphicsPixmapItem
{
public:
    GraphicItem(int x, int y, GraphicsItem type = NOTHING);
    ~GraphicItem();
    void updateGraphic(int newX, int newY);
    GraphicsItem getType();

private:
    void selectIcon();

    int x_;
    int y_;
    GraphicsItem type_;
    int dir_;
    QPixmap picture;

};


}

#endif // GRAPHICITEM_H
