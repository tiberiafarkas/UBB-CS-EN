#include "Courier.h"
#include "Package.h" // Include the Package.h header file
#include <cmath>

Courier::Courier()
{
    // Constructor implementation
}

Courier::Courier(const std::string& name, const std::vector<std::string>& streets, const Zone& zone)
    : name(name), streets(streets), zone(zone)
{
    // Constructor implementation
}

std::string Courier::getName() const
{
    return name;
}

std::vector<std::string>& Courier::getStreets()
{
    return streets;
}

Zone Courier::getZone() const
{
    return zone;
}

bool Courier::isWithinZone(const Location& location) const
{
    int distance = std::sqrt(std::pow(location.x - zone.center, 2) + std::pow(location.y - zone.center, 2));
    return distance <= zone.radius;
}
