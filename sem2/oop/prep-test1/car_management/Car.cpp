#include "Car.h"
#include <string>

Car::Car() : manufacture(""), model(""), year(0), colour("") {}
Car::Car(const std::string& manufacture, const std::string& model, int year, const std::string& colour) :
	manufacture(manufacture), model(model), year(year), colour(colour) {}

Car::~Car() {}

std::string Car::getManufacture() const {
	return this->manufacture;
}

std::string Car::getModel() const {
	return this->model;
}

int Car::getYear() const {
	return this->year;
}

std::string Car::getColour() const {
	return this->colour;
}