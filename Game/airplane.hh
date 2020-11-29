#ifndef AIRPLANE_HH
#define AIRPLANE_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"
#include "graphicitem.h"

#include <QDebug>
#include <QString>

using namespace Interface;

namespace StudentSide{

class airplane: public IActor
{
public:
    airplane();
    ~airplane();

    /**
     * @brief defined in IActor
     */
    Location giveLocation() const override;
    void move(Location loc) override;
    void remove() override;
    bool isRemoved() const override;

    /**
     * @brief Chooses the path the air plane will be taking.
     */
    void path();

protected:
    bool removed_;

private:
    Location location_;
    QString direction_;
};
}
#endif // AIRPLANE_HH
