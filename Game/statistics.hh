#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <QDebug>
#include <QString>
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

    /**
     * @brief Add points to total score.
     * @param Name of the vehicle added to the points.
     */
    void add_points(QString vehicle);

    /**
     * @brief Send the points to be used in the mainwindow.
     * @return The values of points.
     */
    int getPoints();

    /**
     * @brief Send the planes to be used in the mainwindow.
     * @return The value of planes.
     */
    int getPlanes();

    /**
     * @brief Send the buses to be used in the mainwindow.
     * @return The value of buses.
     */
    int getBuses();

private:
    int points_;
    int planes_;
    int buses_;
};
}
#endif // STATISTICS_HH
