#ifndef AIRPLANE_HH
#define AIRPLANE_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

#include <QDebug>
#include <QString>

using namespace Interface;

namespace StudentSide{
/**
 * @brief The Airplane class appers on the map and gives more points than bus
 */
class Airplane: public IActor
{
public:
    Airplane();
    ~Airplane();

    /**
     * @brief defined in IActor
     */
    Location giveLocation() const override;
    void move(Location loc) override;
    void remove() override;
    bool isRemoved() const override;

protected:
    bool removed_;

private:
    Location location_;
};
}
#endif // AIRPLANE_HH
