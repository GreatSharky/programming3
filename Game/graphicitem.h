#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <character.hh>


enum GraphicsItem {NOTHING, STOP, BUS, PLANE , CHARACTER,OTHER};

namespace Aaro {


class GraphicItem: public QGraphicsPixmapItem
{
public:
    GraphicItem(int x, int y, GraphicsItem type = NOTHING);
    ~GraphicItem();
    void updateGraphic(int newX, int newY);
    GraphicsItem getType();
    std::shared_ptr<character> getcharacter();

private:
    void selectIcon();
    void makeCharacter();

    int x_;
    int y_;
    GraphicsItem type_;
    int dir_;
    QPixmap picture;
    std::shared_ptr<character> character_;

};


}

#endif // GRAPHICITEM_H
