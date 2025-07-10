#include "Service.h"
#include "Repository.h"
#include "DynamicArray.h"
#include "Car.h"
#include <string>
#include <iostream>

Service::Service() {}
Service::Service(const Repository& repo) : repo(repo) {}
Service::~Service() {}

bool Service::addCar(Car car) {
	return this->repo.addCar(car);
}

bool Service::removeCar(Car car) {
	return this->repo.removeCar(car);
}

DynamicArray<Car> Service::getCars() const {
	return this->repo.getCars();
}

DynamicArray<Car> Service::sortByManufactureModel() {
	DynamicArray<Car> cars = this->repo.getCars();
	DynamicArray<Car> sorted_cars = cars.copy();
	for (int i = 0; i < cars.getSize() - 1; ++i) {
		for (int j = i + 1; j < cars.getSize(); ++j) {
			if (sorted_cars[i].getManufacture() > sorted_cars[j].getManufacture() ||
				(sorted_cars[i].getManufacture() == sorted_cars[j].getManufacture() && sorted_cars[i].getModel() > sorted_cars[j].getModel())) {
				Car aux = sorted_cars[i];
				sorted_cars[i] = sorted_cars[j];
				sorted_cars[j] = aux;
			}
		}
	}

	return sorted_cars;
}

DynamicArray<Car> Service::sortByColour() {
	DynamicArray<Car> cars = this->repo.getCars();
	DynamicArray<Car> sorted_cars;

	for (int i = 0; i < cars.getSize(); ++i) {
		if (cars[i].getYear() < 1980) {
			sorted_cars.add(cars[i]);
		}
	}

	for (int i = 0; i < sorted_cars.getSize() - 1; ++i) {
		for (int j = i + 1; j < sorted_cars.getSize(); ++j) {
			if (sorted_cars[i].getColour() > sorted_cars[j].getColour()) {
				Car aux = sorted_cars[i];
				sorted_cars[i] = sorted_cars[j];
				sorted_cars[j] = aux;
			}
		}
	}

	return sorted_cars;
}

void Service::addRandomCars() {
	Car car1("Audi", "A4", 2010, "black");
	Car car2("BMW", "X5", 2015, "white");
	Car car3("Mercedes", "E200", 2012, "red");
	Car car4("Audi", "A4", 2010, "black");
	Car car5("BMW", "X7", 2020, "white");
	Car car6("Mercedes", "AClass", 2024, "red");
	Car car7("Mazda", "Miata", 1970, "yellow");
	Car car8("Ford", "Mustang", 1965, "blue");
	Car car9("Chevrolet", "Camaro", 1969, "green");
	this->repo.addCar(car1);
	this->repo.addCar(car2);
	this->repo.addCar(car3);
	this->repo.addCar(car4);
	this->repo.addCar(car5);
	this->repo.addCar(car6);
	this->repo.addCar(car7);
	this->repo.addCar(car8);
	this->repo.addCar(car9);
}