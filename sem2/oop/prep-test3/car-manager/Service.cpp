#include "service.h"

vector<Car> Service::getAllCars() const {
	return this->repository.getAllCars();
}

vector<Car> Service::getCarByMake(const string& make) const {
	vector<Car> result;
	for (auto car : this->repository.getAllCars()) {
		if (car.getMake() == make) {
			result.push_back(car);
		}
	}
	return result;
}