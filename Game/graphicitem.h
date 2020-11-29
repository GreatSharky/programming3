#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <character.hh>


enum GraphicsItem {NOTHING, STOP, BUS, PLANE , CHARACTER,OTHER};

namespace StudentSide {

/**
 * @brief The GraphicItem class controls and creates games graphics
 * works different depending on type
 */
class GraphicItem: public QGraphicsPixmapItem
{
public:
    GraphicItem(int x, int y, GraphicsItem type = NOTHING);
    ~GraphicItem();
    /**
     * @brief Updates the graphics of the actors, its place and direction
     * @param The new X-coordinate
     * @param The new Y-Coordinate
     */
    void updateGraphic(int newX, int newY);
    /**
     * @brief Gives the type of the actor
     * @return The actor type
     */
    GraphicsItem getType();
    /**
     * @brief Gives the pointer to the character
     * @return The pointer oto the character
     */
    std::shared_ptr<Character> getcharacter();

private:
    /**
     * @brief Selects the right icon for the actor
     */
    void selectIcon();
    /**
     * @brief Creates the player character
     */
    void makeCharacter();

    int x_;
    int y_;
    GraphicsItem type_;
    int dir_;
    QPixmap picture;
    std::shared_ptr<Character> character_;

};


}

#endif // GRAPHICITEM_H
