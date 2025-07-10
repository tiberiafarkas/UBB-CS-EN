#include "CourierRepository.h"
#include <string>

CourierRepository::CourierRepository()
{
	std::fstream filecourier(filename);
	if (filecourier.is_open())
	{
		std::string line;
		while (getline(filecourier, line))
		{
			Courier c = this->parseCourier(line);
			couriers.push_back(c);
		}

	}
}

std::vector<Courier> CourierRepository::getAllCouriers()
{
	return this->couriers;
}

void CourierRepository::addCourier(Courier c)
{
	this->couriers.push_back(c);
}

//complete this function to parse couriers from couriers.txt using variables from courier.h
Courier CourierRepository::parseCourier(std::string line)
{
	std::string name;
	std::vector<std::string> streets;
	Zone zone;
	std::string street;
	std::string center;
	std::string radius;
	int i = 0;
	while (line[i] != '|')
	{
		name += line[i];
		i++;
	}
	i++;
	while (line[i] != '|')
	{
		if (line[i] == ';')
		{
			streets.push_back(street);
			street = "";
		}
		else
		{
			street += line[i];
		}
		i++;
	}
	streets.push_back(street); // Add the last street after the loop

	i++;
	while (line[i] != '|')
	{
		center += line[i];
		i++;
	}
	i++;
	while (line[i] != '|')
	{
		radius += line[i];
		i++;
	}
	zone.center = std::stoi(center);
	zone.radius = std::stoi(radius);
	Courier c(name, streets, zone);
	return c;
}

