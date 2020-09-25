#include "nysse.hh"

#include <cassert>
#include <map>
#include <QDebug>


namespace CourseSide
{

Nysse::Nysse(unsigned int line) :
    line_(line),
    name_(QString::number(line).toStdString()),
    stop_(),
    destroyed_(false)

{
}

int Nysse::getSID() const {
    return SID_;
}

void Nysse::setSID(int sid) {
    SID_ = sid;
}

std::string Nysse::getName() const
{
    return name_;
}

std::vector<std::shared_ptr<Interface::IPassenger> > Nysse::getPassengers() const
{
    return passengers_;
}

Interface::Location Nysse::giveLocation() const
{
    return location_;
}

void Nysse::move(Interface::Location loc)
{
    location_ = loc;
}

void Nysse::destroy()
{
    for (std::shared_ptr<Interface::IPassenger> passenger: passengers_) {
        passenger->destroy();
    }
    destroyed_ = true;
}

bool Nysse::isDestroyed() const
{
    return destroyed_;
}

std::map<QTime, std::pair<Interface::Location, std::weak_ptr<Stop> > > Nysse::getTimeRoute() const
{
    return timeroute2_;
}


void Nysse::addPassenger(std::shared_ptr<Interface::IPassenger> passenger)
{
    passengers_.push_back(passenger);
}

void Nysse::removePassenger(std::shared_ptr<Interface::IPassenger> passenger)
{
    for (auto it = passengers_.begin(); it != passengers_.end(); it++) {
        if (it->get() == passenger.get()) {
            passengers_.erase(it);
            break;
        }
    }
}

std::weak_ptr<Stop> Nysse::getFinalStop() const
{
    return timeroute2_.rbegin()->second.second;
}


unsigned int Nysse::getLine()
{
    return line_;
}

std::weak_ptr<Stop> Nysse::getStop()
{
    return stop_;
}

Interface::Location Nysse::moveToNextPosition(QTime time)
{
    // moving the bus to its next location
    // this routine is never called if there isn't next location

    // moving the iterator one step further in the buses route
    // setting the location to the new point

    std::map< QTime, std::pair< Interface::Location, std::weak_ptr<Stop> > >::iterator next = ar2Iterator_;
    ++next ;
    if (next  != timeroute2_.end())
    {
        if (next ->first == time)
        {
            // reached new route point
            ar2Iterator_ = next ;

            // set as stop
            stop_ = ar2Iterator_->second.second;

            // return this new location
            return ar2Iterator_->second.first;
        }
        else
        {
            // portion of distance toward next route point
            double distance = ar2Iterator_->first.secsTo(time) / (double)ar2Iterator_->first.secsTo(next ->first);
            return Interface::Location::calcBetween(ar2Iterator_->second.first, next ->second.first, distance );
        }
    }
    else
    {
        // close the program if it ends up here
        assert(false);
    }
}

void Nysse::calcStartingPos(QTime time)
{
    for (ar2Iterator_ = timeroute2_.begin(); ar2Iterator_ != timeroute2_.end(); ar2Iterator_++) {
        if (time == ar2Iterator_->first) {
            // found the point, when time is the same as inside the game just now

            // there is not necessarily a stop in this point
            location_ = ar2Iterator_->second.first;

            // check the existence of stop for this time
            // Could be that we're currently in point 10.06 and stops are in 10.05 and 10.07
            stop_ = ar2Iterator_->second.second;

            return;

        }
    }
    qDebug() << "SHOULD NEVER GET HERE!!!!!!!";
}

void Nysse::setRoute(const std::map<QTime, std::pair<Interface::Location, std::shared_ptr<Stop> > > &timeroute,
                        QTime &departuretime)
{
    // calculating a new time for every route point from original relative time
    // from data e.g. stop nro 3 in the moment 6 min --> find out what is the ingame
    // time for reaching a stop -> e.g. stop nro 3 is reached at time 10:06
    // also includes route points not only stops

    std::map<QTime, std::pair<Interface::Location, std::weak_ptr<Stop> > > timeroutetimes;
    QTime time = departuretime;

    for (std::pair<QTime, std::pair< Interface::Location, std::shared_ptr<Stop> > > timeroute_point : timeroute) {
        QTime ua;
        ua = time.addSecs( ( timeroute_point.first.hour() *60*60) + ( timeroute_point.first.minute() * 60) + timeroute_point.first.second() );
        timeroutetimes.insert(std::make_pair(ua, std::make_pair(timeroute_point.second.first, timeroute_point.second.second) ));
    }

    // timeroute contains all points of the route every 15 seconds
    timeroute2_ = timeroutetimes;
    // initialisation
    ar2Iterator_ = timeroute2_.begin();
    location_ = ar2Iterator_->second.first;
    Q_ASSERT(getFinalStop().lock() != nullptr);
}

void Nysse::setCity(std::shared_ptr<Interface::ICity> city)
{
    city_ = city;
}

}
