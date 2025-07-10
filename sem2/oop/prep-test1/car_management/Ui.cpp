#include "Ui.h"
#include "Service.h"
#include "Repository.h"
#include "DynamicArray.h"
#include "Car.h"
#include <string>
#include <iostream>

UI::UI() {
	this->service = Service();
}

UI::~UI() {}


void UI::printMenu() {
	std::cout << "1. Add car\n";
	std::cout << "2. Remove car\n";
	std::cout << "3. Print cars sorted by manufacture and model\n";
	std::cout << "4. Print vintage cars sorted by colour\n";
	std::cout << "5. Print cars\n";
	std::cout << "0. Exit\n";
}

void UI::addCar() {
	std::string manufacture, model, colour;
	int year;
	std::cout << "Manufacture: ";
	std::cin >> manufacture;
	std::cout << "Model: ";
	std::cin >> model;
	std::cout << "Year: ";
	std::cin >> year;
	std::cout << "Colour: ";
	std::cin >> colour;
	Car car(manufacture, model, year, colour);
	if ( this->service.addCar(car) ) 
		std::cout << "Car added successfully!\n";
	else
		std::cout << "Car already exists!\n";
}

void UI::removeCar() {
	std::string manufacture, model, colour;
	int year;
	std::cout << "Manufacture: ";
	std::cin >> manufacture;
	std::cout << "Model: ";
	std::cin >> model;
	std::cout << "Year: ";
	std::cin >> year;
	std::cout << "Colour: ";
	std::cin >> colour;
	Car car(manufacture, model, year, colour);
	if (this->service.removeCar(car))
		std::cout << "Car removed successfully!\n";
	else
		std::cout << "Car does not exist!\n";
}

void UI::printCarsSortedByManufactureModel() {
	DynamicArray<Car> cars = this->service.sortByManufactureModel();
	for (int i = 0; i < cars.getSize(); ++i) {
		std::cout << cars[i].getManufacture() << " | " << cars[i].getModel() << " | " << cars[i].getYear() << " | " << cars[i].getColour() << "\n";
	}
}

void UI::printVintageCarsSortedByColour() {
	DynamicArray<Car> cars = this->service.sortByColour();
	for (int i = 0; i < cars.getSize(); ++i) {
		std::cout << cars[i].getManufacture() << " | " << cars[i].getModel() << " | " << cars[i].getYear() << " | " << cars[i].getColour() << "\n";
	}
}

void UI::printCars() {
	DynamicArray<Car> cars = this->service.getCars();
	for (int i = 0; i < cars.getSize(); ++i) {
		std::cout << cars[i].getManufacture() << " | " << cars[i].getModel() << " | " << cars[i].getYear() << " | " << cars[i].getColour() << "\n";
	}
}

void UI::run() {
	int option;
	this->service.addRandomCars();
	while (true) {
		this->printMenu();
		std::cout << "Option: ";
		std::cin >> option;
		switch (option) {
		case(1):
			this->addCar();
			break;

		case(2):
			this->removeCar();
			break;

		case(3):
			this->printCarsSortedByManufactureModel();
			break;

		case(4):
			this->printVintageCarsSortedByColour();
			break;

		case(5):
			this->printCars();
			break;

		case(0):
			return;

		default:
			std::cout << "Invalid option!\n";
		}
	}
}