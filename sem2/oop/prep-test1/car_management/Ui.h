#pragma once
#include "Service.h"
#include "Repository.h"
#include "DynamicArray.h"
#include "Car.h"
#include <string>
#include <iostream>

class UI {
private:
	Service service;

public:
	//constructor
	UI();
	UI(const Service& service) : service(service) {}

	//destructor
	~UI();

	void printMenu();
	void addCar();
	void removeCar();
	void printCarsSortedByManufactureModel();
	void printVintageCarsSortedByColour();
	void printCars();
	void run();
};