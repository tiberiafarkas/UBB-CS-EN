#pragma once
#include "DynamicArray.h"
#include "Car.h"
#include "Repository.h"
#include <string>

class Service {
private:
	Repository repo;

public:
	//constructor
	Service();
	Service(const Repository& repo);

	//destructor
	~Service();

	bool addCar(Car car);
	bool removeCar(Car car);
	DynamicArray<Car> getCars() const;
	DynamicArray<Car> sortByManufactureModel();
	DynamicArray<Car> sortByColour();
	void addRandomCars();
};