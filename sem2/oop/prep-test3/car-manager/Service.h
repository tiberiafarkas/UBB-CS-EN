#pragma once
#include "repository.h"

class Service {
private:
	Repository repository;

public:
	vector<Car> getAllCars() const;
	vector<Car> getCarByMake(const string& make) const;
};