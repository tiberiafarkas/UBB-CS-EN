#pragma once

#include<iostream>
using namespace std;

class Star
{
private:
	string name, constellation;
	int ra, diameter;
	double dec;
public:
    explicit Star(std::string name = "", std::string constellation = "", int ra = 0, double dec = 0, int diameter = 0) : name{ name },
        constellation{ constellation },
        ra{ ra },
        dec{ dec },
        diameter{ diameter } {};
    [[nodiscard]] std::string getName() const { return this->name; }
    [[nodiscard]] std::string getConstellation() const { return this->constellation; }
    [[nodiscard]] int getRa() const { return this->ra; }
    [[nodiscard]] double getDec() const { return this->dec; }
    [[nodiscard]] int getDiameter() const { return this->diameter; }
	 inline bool operator < (const Star& other) const
    {
        return this->constellation < other.constellation;
    }
};

