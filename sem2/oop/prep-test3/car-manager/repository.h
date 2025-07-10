#pragma once
#include "car.h"
#include <vector>

using std::vector;

class Repository {
private:
	vector<Car> cars;

public:
	Repository() {
		this->load();
	}
	void load();
	vector<Car> getAllCars() const;
	~Repository() {}
};