#ifndef AIRPLANE_HH
#define AIRPLANE_HH
#include "interfaces/iactor.hh"
#include "core/location.hh"

#include <QDebug>
#include <QString>

using namespace Interface;

namespace Aaro{

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

    void path();

protected:
    bool removed_;

private:
    Location location_;
    QString direction_;
};
}
#endif // AIRPLANE_HH
