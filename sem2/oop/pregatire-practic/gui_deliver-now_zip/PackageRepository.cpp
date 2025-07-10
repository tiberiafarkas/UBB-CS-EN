#include "PackageRepository.h"
#include "Package.h"

PackageRepository::PackageRepository()
{
	std::fstream filepackage(filename);
	if (filepackage.is_open())
	{
		std::string line;
		while (getline(filepackage, line))
		{
			Package p = this->parsePackage(line);
			packages.push_back(p);
		}

	}
}

std::vector<Package> PackageRepository::getAllPackages()
{
	return this->packages;
}

//add a package to the vector of packages
void PackageRepository::addPackage(Package p)
{
	this->packages.push_back(p);
}

//do it like in CourierRepository.cpp but with Package variables from Package.h
Package PackageRepository::parsePackage(std::string line)
{
	std::string recipient;
	std::string address;
	std::string locationX;
	std::string locationY;
	std::string status;

	int i = 0;

	while (line[i] != '|')
	{
		recipient += line[i];
		i++;
	}

	i++;
	while (line[i] != '|')
	{
		address += line[i];
		i++;
	}

	i++;
	while (line[i] != '|')
	{
		locationX += line[i];
		i++;
	}

	i++;
	while (line[i] != '|')
	{
		locationY += line[i];
		i++;
	}

	i++;
	while (line[i] != '|')
	{
		status += line[i];
		i++;
	}

	Location location;
	location.x = std::stoi(locationX);
	location.y = std::stoi(locationY);

	bool packageStatus = (status == "true");

	Package p(recipient, address, location, packageStatus);
	return p;
}

//get a package by sender and address
Package& PackageRepository::getPackageBySenderAndAddress(std::string sender, std::string address)
{
	for (auto& p : this->packages)
	{
		if (p.getRecipient() == sender && p.getAddress() == address)
		{
			return p;
		}
	}
	throw std::runtime_error("Package not found");
}