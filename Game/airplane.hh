#ifndef AIRPLANE_HH
#define AIRPLANE_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

#include <QDebug>
#include <QString>

using namespace Interface;

namespace StudentSide{

class Airplane: public IActor
{
public:
    Airplane(int x, int y);
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
