#ifndef STOPGRAPHIC_H
#define STOPGRAPHIC_H

#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>


namespace  Aaro {


class StopGraphic: public QGraphicsPixmapItem
{
public:
    StopGraphic(int x, int y, int type);
    int giveType();

private:
    QPixmap *pic;
    int type_;
    QString filename;
};
}

#endif // STOPGRAPHIC_H
