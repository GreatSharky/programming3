#ifndef CHARACTER_HH
#define CHARACTER_HH
#include <QDebug>
#include <QGraphicsItem>
#include <QKeyEvent>

#include "interfaces/iactor.hh"
#include "core/location.hh"

using namespace Interface;

namespace Aaro{


class character: public IActor
{
public:
    /**
     * @brief character
     */
    character();
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
     * @param event buttonclicks
     */

    void movement_commands(QKeyEvent *event);

protected:
    bool removed_;

private:
    Location location_;

};
}
#endif // CHARACTER_HH
