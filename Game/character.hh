#ifndef CHARACTER_HH
#define CHARACTER_HH
#include <QDebug>
#include <QGraphicsItem>
#include <QKeyEvent>

#include "interfaces/iactor.hh"
#include "core/location.hh"


using namespace Interface;

namespace StudentSide{

/**
 * @brief The Character class the actor that player controls and eats buses and planes
 */
class Character: public IActor
{
public:
    Character(int x, int y);
    ~Character();

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

protected:
    bool removed_; 

private:
    Location location_;

};
}
#endif // CHARACTER_HH
