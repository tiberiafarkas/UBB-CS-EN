#include "Repository.h"
#include<sstream>
#include<algorithm>

void Repository::loadAstronauts()
{
    std::ifstream input(this->astronautsFileName);
    const char sep = '|';
    std::string line, name, constellation;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::getline(iss, name, sep);
        std::getline(iss, constellation, sep);
        this->astronauts.emplace_back(name, constellation);
    }
}

void Repository::loadStars() {
    std::ifstream input(this->starsFileName);
    const char sep = '|';
    std::string line, name, constellation, ra, dec, diameter;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::getline(iss, name, sep);
        std::getline(iss, constellation, sep);
        std::getline(iss, ra, sep);
        std::getline(iss, dec, sep);
        std::getline(iss, diameter, sep);
        this->stars.emplace_back(name, constellation, std::stoi(ra), std::stod(dec), std::stoi(diameter));
    }
}

Repository::~Repository()
{
    std::sort(this->stars.begin(), this->stars.end());
    std::ofstream output(this->starsFileName);
    for (auto& star : this->stars)
        output << star.getName() << '|' << star.getConstellation() << '|' << star.getRa() << '|' << star.getDec()  << '|' << star.getDiameter() <<  '\n';
    output.close();
}