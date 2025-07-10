#pragma once
#include "DynamicArray.h"
#include "Car.h"

class Repository {
private:
	DynamicArray<Car> cars;

public:
	//constructor
	Repository();
	
	//destructor
	~Repository();

	bool addCar(const Car& car);
	bool removeCar(Car car);
	DynamicArray<Car> getCars() const;
};
