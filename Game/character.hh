#ifndef CHARACTER_HH
#define CHARACTER_HH
#include <QDebug>
#include <QGraphicsItem>
#include <QKeyEvent>

#include "interfaces/iactor.hh"
#include "core/location.hh"
#include "graphicitem.h"

using namespace Interface;

namespace Aaro{

class character: public IActor
{
public:
    character(int x, int y);
    ~character();

    /**
     * @brief defined in IActor
     */
    Location giveLocation() const override;
    void move(Location loc) override;
    void remove() override;
    bool isRemoved() const override;
    /**
     * @brief Takes the user inputs
     * @param command right direction
     */

    void movement_commands(QString command);

    /**
     * @brief getGraphic
     * @return characters graphic
     */
    GraphicItem *getGraphic();

protected:
    bool removed_; 

private:
    Location location_;
    GraphicItem * graphic;
};
}
#endif // CHARACTER_HH
