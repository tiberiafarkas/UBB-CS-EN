#pragma once

#include <string>
#include <vector>
#include "Package.h" // Include the Package.h header file

struct Zone {
    int center;
    int radius;
};

class Courier
{
private:
    std::string name;
    std::vector<std::string> streets;
    Zone zone;
public:
    Courier();
    Courier(const std::string& name, const std::vector<std::string>& streets, const Zone& zone);
    std::string getName() const;
    std::vector<std::string>& getStreets();
    Zone getZone() const;
    bool isWithinZone(const Location& location) const; // Declare the function here
    ~Courier() = default;
};
