#pragma once
#include <vector>
#include "Courier.h"
#include <fstream>
#include <sstream>

class CourierRepository
{
private:
	std::vector<Courier> couriers;
	std::string filename = "couriers.txt";
public:
	CourierRepository();
	std::vector<Courier> getAllCouriers();
	void addCourier(Courier c);
	Courier parseCourier(std::string line);
	~CourierRepository() = default;
};

