#ifndef ISTATISTICS_HH
#define ISTATISTICS_HH

/**
  * @file
  * @brief Defines an interface for scoring statistics.
  */

namespace Interface
{

/**
 * @brief StatisticsIF is an interface, which defines an object that manages scoring statistics.
 *
 * If class method doesn't have exception guarantee of nothrow, method can leak out exception `std::bad_alloc` (out of memory)
 */
class IStatistics
{
public:
    /**
      * @brief Default constructor for the Interface.(For documentation).
      * @post Scores are reset by default.
      */
    IStatistics() = default;

    /**
      * @brief Interface has default virtual destructor (base class needs to have a virtual destructor).
      */
    virtual ~IStatistics() = default;

    /**
     * @brief givePoints returns current score in the game.
     * @pre -
     * @return score
     * @post Exception guarantee: nothrow
     */
    virtual int givePoints() const = 0;

    /**
     * @brief passengerDied notifies, that the passanger is dead.
     * @param num how many passangers eliminated.
     * @pre num > 0
     * @post Exception guarantee: strong
     */
    virtual void passengerDied(int num) = 0;

    /**
     * @brief morePassengers notifies, that more passangers are added to the game.
     * @param num how many new passangers are added.
     * @pre num > 0
     * @post Exception guarantee: strong
     */
    virtual void morePassengers(int num) = 0;

    /**
     * @brief nysseDestroyed notifies, that the nysse is destroyed ingame.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void nysseDestroyed() = 0;

    /**
     * @brief newNysse notifies, that a new nysse is added to the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void newNysse() = 0;

    /**
     * @brief nysseLeft notifies, that a nysse has left the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void nysseLeft() = 0;
};

}

#endif // ISTATISTICS_HH
