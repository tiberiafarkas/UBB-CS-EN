#include "Repository.h"
#include "DynamicArray.h"
#include "Car.h"
#include <string>
#include <iostream>

Repository::Repository() {
	this->cars = DynamicArray<Car>();
}
Repository::~Repository() {}

bool Repository::addCar(const Car& car) {
	for (int i = 0; i < this->cars.getSize(); ++i) {
		if (cars[i].getModel() == car.getModel() && cars[i].getYear() == car.getYear())
			return false;
	}

	this->cars.add(car);
	return true;
}

DynamicArray<Car> Repository::getCars() const {
	return this->cars;
}

bool Repository::removeCar(Car car) {
	for (int i = 0; i < this->cars.getSize(); ++i) {
		if (cars[i].getManufacture() == car.getManufacture() && cars[i].getModel() == car.getModel() && cars[i].getYear() == car.getYear() && cars[i].getColour() == car.getColour()) {
			this->cars.remove(i);
			return true;
		}
	}
	return false;
}