#pragma once
#include "Repository.h"

class Service
{
private:
	Repository &repository;
public:
	explicit Service(Repository &repository) : repository{ repository } {};
	vector<Astronaut> &getAstronauts() { return repository.getAstronauts(); }
	vector<Star> &getStars() { return repository.getStars(); }
	void addStar(const string& name, const string& constellation, const int& ra, const double& dec, const int& diameter);
	vector<Star> getStarsFiltered(const string& name);
};

