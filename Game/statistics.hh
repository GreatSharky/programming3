#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <QDebug>
#include "interfaces/istatistics.hh"

using namespace Interface;

namespace Aaro{

class statistics : public IStatistics
{
public:
    statistics();
    ~statistics();
    /**
     * @brief defined in IStatistics
     */

    void morePassengers(int num) override;
    void nysseRemoved() override;
    void newNysse() override;
    void nysseLeft() override;

    void add_points(int new_points);

private:
    int points_;
};
}
#endif // STATISTICS_HH
