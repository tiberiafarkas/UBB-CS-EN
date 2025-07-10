#include "Service.h"

void Service::addStar(const string& name, const string& constellation, const int& ra, const double& dec, const int& diameter)
{
	Star star{ name, constellation, ra, dec, diameter };
	if (name.empty() or dec <= 0) 
		throw std::invalid_argument("Invalid star");
	this->repository.addStar(star);
}

vector<Star> Service::getStarsFiltered(const string& name)
{
	vector<Star> stars = this->repository.getStars();
	vector<Star> filteredStars;
	for (auto& star : stars)
		if (star.getName().find(name) != std::string::npos)
			filteredStars.push_back(star);
	return filteredStars;
}